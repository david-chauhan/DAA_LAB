
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int has_duplicate_brute(int arr[], int n, long *comparisons) {
    long comp = 0;
    int found = 0;
    for (int i = 0; i < n && !found; i++) {
        for (int j = i + 1; j < n; j++) {
            comp++;
            if (arr[i] == arr[j]) { found = 1; break; }
        }
    }
    *comparisons = comp;
    return found;
}

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int has_duplicate_sort(int arr[], int n, long *comparisons) {
    int *copy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    qsort(copy, n, sizeof(int), cmp_int); 

    long comp = 0;
    int found = 0;
    for (int i = 0; i < n - 1; i++) {
        comp++;
        if (copy[i] == copy[i + 1]) { found = 1; break; }
    }
    *comparisons = comp;
    free(copy);
    return found;
}

void fill_unique_permutation(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
    }
}

int main(void) {
    srand((unsigned) time(NULL));

    int sizes[] = {100, 500, 1000, 2000, 4000, 8000};
    int n_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *fp = fopen("uniqueness_results.csv", "w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open uniqueness_results.csv\n");
        return 1;
    }
    fprintf(fp, "n,brute_comparisons,brute_time_sec,sort_comparisons,sort_time_sec,duplicate_found\n");

    printf("Worst case: array has NO duplicates (brute force cannot exit early)\n");
    printf("%-6s %-16s %-12s %-16s %-12s %-10s\n",
           "n", "Brute comps", "Brute t(s)", "Sort comps", "Sort t(s)", "Duplicate?");

    for (int s = 0; s < n_sizes; s++) {
        int n = sizes[s];
        int *arr = malloc(n * sizeof(int));
        fill_unique_permutation(arr, n); 

        long comp_brute, comp_sort;
        clock_t t0, t1;

        t0 = clock();
        int dup_brute = has_duplicate_brute(arr, n, &comp_brute);
        t1 = clock();
        double time_brute = (double)(t1 - t0) / CLOCKS_PER_SEC;

        t0 = clock();
        int dup_sort = has_duplicate_sort(arr, n, &comp_sort);
        t1 = clock();
        double time_sort = (double)(t1 - t0) / CLOCKS_PER_SEC;

        printf("%-6d %-16ld %-12.6f %-16ld %-12.6f %-10s\n",
               n, comp_brute, time_brute, comp_sort, time_sort,
               dup_brute ? "yes" : "no");

        fprintf(fp, "%d,%ld,%.6f,%ld,%.6f,%s\n",
                n, comp_brute, time_brute, comp_sort, time_sort,
                dup_brute ? "yes" : "no");

        if (dup_brute != dup_sort) {
            fprintf(stderr, "WARNING: methods disagree for n=%d!\n", n);
        }

        free(arr);
    }
    fclose(fp);

    printf("\nResults written to uniqueness_results.csv\n");
    printf("Conclusion: brute force does O(n^2) comparisons in the worst\n");
    printf("case (no duplicates -> must check every pair), while sorting\n");
    printf("first reduces this to O(n log n) comparisons plus one O(n)\n");
    printf("scan. For sufficiently large n the sort-based method is far\n");
    printf("faster; the gap widens quickly as n grows.\n");

    return 0;
}
