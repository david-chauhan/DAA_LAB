#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double v, w, lambda;
    int used;
} Item;

double schedule(Item *it, int n, double W, int verbose)
{
    double t = 0, total = 0;
    int step = 0;
    while (t < W) {
        int best = -1;
        double bestd = 0;
        for (int i = 0; i < n; i++) {
            if (it[i].used)
                continue;
            double d = it[i].v / it[i].w - it[i].lambda * t;
            if (d > bestd) {
                bestd = d;
                best = i;
            }
        }
        if (best < 0)
            break;
        double amt = it[best].w < W - t ? it[best].w : W - t;
        double gain = amt * bestd;
        if (verbose)
            printf("  %d. item %d: take %.4f of %.4f (fraction %.4f) at t=%.4f, density %.4f, gain %.4f\n",
                   ++step, best + 1, amt, it[best].w, amt / it[best].w, t, bestd, gain);
        total += gain;
        t += amt;
        it[best].used = 1;
    }
    return total;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n;
    double W;
    printf("Enter number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    Item *it = malloc((size_t)n * sizeof(Item));
    for (int i = 0; i < n; i++) {
        printf("Enter value, weight and decay rate of item %d: ", i + 1);
        if (scanf("%lf %lf %lf", &it[i].v, &it[i].w, &it[i].lambda) != 3 || it[i].w <= 0 || it[i].lambda <= 0) {
            printf("Invalid input\n");
            return 1;
        }
        it[i].used = 0;
    }
    printf("Enter knapsack capacity W: ");
    if (scanf("%lf", &W) != 1 || W < 0) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Schedule:\n");
    double total = schedule(it, n, W, 1);
    printf("Maximum total value: %.4f\n", total);
    free(it);
    return 0;
}
