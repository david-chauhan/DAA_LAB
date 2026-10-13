#include <stdio.h>
#include <stdlib.h>

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int min_rooms(int *start, int *end, int n)
{
    qsort(start, (size_t)n, sizeof(int), cmp_int);
    qsort(end, (size_t)n, sizeof(int), cmp_int);
    int rooms = 0, j = 0;
    for (int i = 0; i < n; i++) {
        if (start[i] >= end[j])
            j++;
        else
            rooms++;
    }
    return rooms;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n;
    printf("Enter number of meetings: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    int *start = malloc((size_t)n * sizeof(int));
    int *end = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Enter start and end time of meeting %d: ", i + 1);
        if (scanf("%d %d", &start[i], &end[i]) != 2 || end[i] < start[i]) {
            printf("Invalid input\n");
            return 1;
        }
    }
    printf("Minimum number of rooms: %d\n", min_rooms(start, end, n));
    free(start);
    free(end);
    return 0;
}
