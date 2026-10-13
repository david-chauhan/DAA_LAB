#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

void hu_tucker_levels(const ll *w, int n, int *level)
{
    if (n == 1) {
        level[0] = 0;
        return;
    }
    ll *sw = malloc((size_t)n * sizeof(ll));
    int *sq = malloc((size_t)n * sizeof(int));
    int *sid = malloc((size_t)n * sizeof(int));
    int *parent = malloc((size_t)(2 * n - 1) * sizeof(int));
    int *depth = calloc((size_t)(2 * n - 1), sizeof(int));
    for (int i = 0; i < n; i++) {
        sw[i] = w[i];
        sq[i] = 1;
        sid[i] = i;
    }
    for (int i = 0; i < 2 * n - 1; i++)
        parent[i] = -1;
    int m = n, next = n;
    while (m > 1) {
        ll bestsum = LLONG_MAX;
        int bp = -1, bq = -1, s = 0;
        for (;;) {
            int e = s + 1;
            while (e < m - 1 && !sq[e])
                e++;
            int p1 = -1, p2 = -1;
            for (int i = s; i <= e; i++) {
                if (p1 < 0 || sw[i] < sw[p1]) {
                    p2 = p1;
                    p1 = i;
                } else if (p2 < 0 || sw[i] < sw[p2]) {
                    p2 = i;
                }
            }
            ll sum = sw[p1] + sw[p2];
            if (sum < bestsum) {
                bestsum = sum;
                bp = p1 < p2 ? p1 : p2;
                bq = p1 < p2 ? p2 : p1;
            }
            if (e == m - 1)
                break;
            s = e;
        }
        int id = next++;
        parent[sid[bp]] = id;
        parent[sid[bq]] = id;
        sw[bq] = bestsum;
        sq[bq] = 0;
        sid[bq] = id;
        for (int k = bp; k < m - 1; k++) {
            sw[k] = sw[k + 1];
            sq[k] = sq[k + 1];
            sid[k] = sid[k + 1];
        }
        m--;
    }
    for (int i = next - 2; i >= 0; i--)
        depth[i] = depth[parent[i]] + 1;
    for (int i = 0; i < n; i++)
        level[i] = depth[i];
    free(sw);
    free(sq);
    free(sid);
    free(parent);
    free(depth);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n;
    printf("Enter number of weights: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    ll *w = malloc((size_t)n * sizeof(ll));
    printf("Enter %d weights in order: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &w[i]) != 1 || w[i] <= 0) {
            printf("Invalid input\n");
            return 1;
        }
    }
    int *level = malloc((size_t)n * sizeof(int));
    hu_tucker_levels(w, n, level);
    int maxlev = 0;
    for (int i = 0; i < n; i++)
        if (level[i] > maxlev)
            maxlev = level[i];
    char *code = malloc((size_t)maxlev + 2);
    int cl = level[0];
    memset(code, '0', (size_t)cl);
    code[cl] = '\0';
    ll cost = 0;
    printf("Optimal alphabetic tree:\n");
    printf("  Index  Weight  Depth  Code\n");
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            int p = cl - 1;
            while (p >= 0 && code[p] == '1')
                code[p--] = '0';
            if (p >= 0)
                code[p] = '1';
            while (cl < level[i])
                code[cl++] = '0';
            cl = level[i];
            code[cl] = '\0';
        }
        printf("  %-5d  %-6lld  %-5d  %s\n", i + 1, w[i], level[i], cl ? code : "(empty)");
        cost += w[i] * level[i];
    }
    printf("Minimum cost (sum of weight * depth): %lld\n", cost);
    free(w);
    free(level);
    free(code);
    return 0;
}
