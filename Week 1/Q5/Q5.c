
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int find_partition_point(int arr[], int n) {
    int lo = 0, hi = n; 
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == 1) {
            hi = mid;
        } else {
            lo = mid + 1; 
        }
    }
    return lo;
}

void print_array(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : ",");
    }
    printf("]\n");
}

int main(void) {
    int t1[] = {0, 0, 0, 0, 1, 1, 1};
    int t2[] = {0, 0, 0, 0, 0, 0};
    int t3[] = {1, 1, 1, 1};
    int t4[] = {0};
    int t5[] = {1};

    int *tests[] = {t1, t2, t3, t4, t5};
    int sizes[]  = {7, 6, 4, 1, 1};

    for (int i = 0; i < 5; i++) {
        printf("Array: ");
        print_array(tests[i], sizes[i]);
        int idx = find_partition_point(tests[i], sizes[i]);
        printf("  -> Partition point (first index with 1) = %d\n\n", idx);
    }

    srand((unsigned) time(NULL));
    int n = 20;
    int arr[20];
    int split = rand() % (n + 1); 
    for (int i = 0; i < n; i++) arr[i] = (i < split) ? 0 : 1;

    printf("Randomised test, n = %d\n", n);
    printf("Array: ");
    print_array(arr, n);

    int binary_result = find_partition_point(arr, n);

    int linear_result = n;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) { linear_result = i; break; }
    }

    printf("Binary search result: %d\n", binary_result);
    printf("Linear scan result:   %d\n", linear_result);
    printf("%s\n", (binary_result == linear_result) ? "MATCH (correct)" : "MISMATCH (bug!)");

    printf("\nComplexity: binary search does this in O(log n) time,\n");
    printf("compared to O(n) for a naive left-to-right scan.\n");

    return 0;
}
