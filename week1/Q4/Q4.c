
#include <stdio.h>
#include <stdlib.h>

long move_count = 0;

void hanoi(int n, char from, char aux, char to, int print_moves) {
    if (n == 0) return;
    hanoi(n - 1, from, to, aux, print_moves);
    move_count++;
    if (print_moves) {
        printf("Move disc %d from %c to %c\n", n, from, to);
    }
    hanoi(n - 1, aux, from, to, print_moves);
}

int main(void) {
  
    printf("Demo run for n = 3 discs:\n");
    move_count = 0;
    hanoi(3, 'A', 'B', 'C', 1);
    printf("Total moves for n = 3: %ld (expected %ld)\n\n", move_count, (long) ((1L << 3) - 1));

    int max_n = 20;   
    FILE *fp = fopen("hanoi_results.csv", "w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open hanoi_results.csv\n");
        return 1;
    }
    fprintf(fp, "n,moves,expected_2n_minus_1\n");

    printf("%-6s %-15s %-15s\n", "n", "Moves (actual)", "2^n - 1 (theory)");
    for (int n = 1; n <= max_n; n++) {
        move_count = 0;
        hanoi(n, 'A', 'B', 'C', 0);
        long expected = (1L << n) - 1;
        printf("%-6d %-15ld %-15ld\n", n, move_count, expected);
        fprintf(fp, "%d,%ld,%ld\n", n, move_count, expected);
    }
    fclose(fp);

    printf("\nResults written to hanoi_results.csv\n");
    printf("Conclusion: moves(n) = 2^n - 1 exactly, matching the\n");
    printf("recurrence T(n) = 2*T(n-1) + 1, T(0) = 0. This is EXPONENTIAL\n");
    printf("growth (O(2^n)), so ToH quickly becomes infeasible for large n\n");
    printf("(e.g. n = 64 would need over 1.8 x 10^19 moves).\n");

    return 0;
}
