#include <stdio.h>
#include <stdlib.h>

long long candies(const int *r, int n, int *c)
{
    for (int i = 0; i < n; i++)
        c[i] = 1;
    for (int i = 1; i < n; i++)
        if (r[i] > r[i - 1])
            c[i] = c[i - 1] + 1;
    for (int i = n - 2; i >= 0; i--)
        if (r[i] > r[i + 1] && c[i] <= c[i + 1])
            c[i] = c[i + 1] + 1;
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += c[i];
    return sum;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n;
    printf("Enter number of children: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    int *r = malloc((size_t)n * sizeof(int));
    int *c = malloc((size_t)n * sizeof(int));
    printf("Enter %d ratings: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &r[i]) != 1) {
            printf("Invalid input\n");
            return 1;
        }
    }
    long long total = candies(r, n, c);
    printf("Candies:");
    for (int i = 0; i < n; i++)
        printf(" %d", c[i]);
    printf("\n");
    printf("Minimum total candies: %lld\n", total);
    free(r);
    free(c);
    return 0;
}
