
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int toss_coin(double p) {
    double r = (double) rand() / ((double) RAND_MAX + 1.0);
    return (r < p) ? 1 : 0;
}

double simulate(double p, long trials) {
    long heads = 0;
    for (long i = 0; i < trials; i++) {
        heads += toss_coin(p);
    }
    return (double) heads / (double) trials;
}

int main(void) {
    srand((unsigned) time(NULL));

    long trial_counts[] = {100, 1000, 10000, 100000, 1000000};
    int n_counts = sizeof(trial_counts) / sizeof(trial_counts[0]);

    printf("=== Fair coin (p = 0.5) ===\n");
    printf("%-12s %-15s\n", "Tosses", "P(HEAD) observed");
    for (int i = 0; i < n_counts; i++) {
        double prob = simulate(0.5, trial_counts[i]);
        printf("%-12ld %-15.5f\n", trial_counts[i], prob);
    }

    printf("\n=== Biased coin (p = 0.7) ===\n");
    printf("%-12s %-15s\n", "Tosses", "P(HEAD) observed");
    for (int i = 0; i < n_counts; i++) {
        double prob = simulate(0.7, trial_counts[i]);
        printf("%-12ld %-15.5f\n", trial_counts[i], prob);
    }

    FILE *fp = fopen("coin_results.csv", "w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open coin_results.csv for writing\n");
        return 1;
    }
    fprintf(fp, "tosses,fair_estimate,biased_estimate\n");
    for (int i = 0; i < n_counts; i++) {
        double fair_p = simulate(0.5, trial_counts[i]);
        double biased_p = simulate(0.7, trial_counts[i]);
        fprintf(fp, "%ld,%.5f,%.5f\n", trial_counts[i], fair_p, biased_p);
    }
    fclose(fp);
    printf("\nResults written to coin_results.csv (plot P(HEAD) vs tosses)\n");

    return 0;
}
