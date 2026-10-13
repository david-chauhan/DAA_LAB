#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int overlap(const char *a, const char *b)
{
    int la = (int)strlen(a), lb = (int)strlen(b);
    int m = la < lb ? la : lb;
    for (int k = m; k > 0; k--)
        if (memcmp(a + la - k, b, (size_t)k) == 0)
            return k;
    return 0;
}

int remove_contained(char **s, int n)
{
    int k = 0;
    for (int i = 0; i < n; i++) {
        int drop = 0;
        for (int j = 0; j < n && !drop; j++) {
            if (i == j)
                continue;
            if (strstr(s[j], s[i]) != NULL && (strlen(s[j]) > strlen(s[i]) || j < i))
                drop = 1;
        }
        if (!drop)
            s[k++] = s[i];
    }
    return k;
}

typedef struct {
    int i, j, ov;
} Edge;

static int cmp_edge(const void *a, const void *b)
{
    const Edge *x = a, *y = b;
    if (x->ov != y->ov)
        return y->ov - x->ov;
    if (x->i != y->i)
        return x->i - y->i;
    return x->j - y->j;
}

static int find(int *uf, int x)
{
    while (uf[x] != x) {
        uf[x] = uf[uf[x]];
        x = uf[x];
    }
    return x;
}

char *greedy_superstring(char **s, int n)
{
    int total = 1;
    for (int i = 0; i < n; i++)
        total += (int)strlen(s[i]);
    char *out = malloc((size_t)total);
    if (n == 1) {
        strcpy(out, s[0]);
        return out;
    }
    int *ov = malloc((size_t)n * n * sizeof(int));
    Edge *e = malloc((size_t)n * n * sizeof(Edge));
    int ne = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            ov[i * n + j] = overlap(s[i], s[j]);
            e[ne].i = i;
            e[ne].j = j;
            e[ne].ov = ov[i * n + j];
            ne++;
        }
    }
    qsort(e, (size_t)ne, sizeof(Edge), cmp_edge);
    int *succ = malloc((size_t)n * sizeof(int));
    int *pred = malloc((size_t)n * sizeof(int));
    int *uf = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        succ[i] = pred[i] = -1;
        uf[i] = i;
    }
    for (int k = 0; k < ne; k++) {
        int i = e[k].i, j = e[k].j;
        if (succ[i] < 0 && pred[j] < 0 && find(uf, i) != find(uf, j)) {
            succ[i] = j;
            pred[j] = i;
            uf[find(uf, i)] = find(uf, j);
        }
    }
    int cur = 0;
    while (pred[cur] >= 0)
        cur = pred[cur];
    strcpy(out, s[cur]);
    while (succ[cur] >= 0) {
        int nx = succ[cur];
        strcat(out, s[nx] + ov[cur * n + nx]);
        cur = nx;
    }
    free(ov);
    free(e);
    free(succ);
    free(pred);
    free(uf);
    return out;
}

char *optimal_superstring(char **s, int n)
{
    int *ov = malloc((size_t)n * n * sizeof(int));
    int *len = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        len[i] = (int)strlen(s[i]);
        for (int j = 0; j < n; j++)
            ov[i * n + j] = i == j ? 0 : overlap(s[i], s[j]);
    }
    int full = (1 << n) - 1;
    int *dp = malloc((size_t)(full + 1) * n * sizeof(int));
    int *par = malloc((size_t)(full + 1) * n * sizeof(int));
    for (int i = 0; i < (full + 1) * n; i++) {
        dp[i] = 1 << 30;
        par[i] = -1;
    }
    for (int i = 0; i < n; i++)
        dp[(1 << i) * n + i] = len[i];
    for (int mask = 1; mask <= full; mask++) {
        for (int i = 0; i < n; i++) {
            int cur = dp[mask * n + i];
            if (!(mask & (1 << i)) || cur >= (1 << 30))
                continue;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j))
                    continue;
                int nm = mask | (1 << j);
                int v = cur + len[j] - ov[i * n + j];
                if (v < dp[nm * n + j]) {
                    dp[nm * n + j] = v;
                    par[nm * n + j] = i;
                }
            }
        }
    }
    int last = 0;
    for (int i = 1; i < n; i++)
        if (dp[full * n + i] < dp[full * n + last])
            last = i;
    int *order = malloc((size_t)n * sizeof(int));
    int mask = full, k = n;
    while (last >= 0) {
        order[--k] = last;
        int p = par[mask * n + last];
        mask ^= 1 << last;
        last = p;
    }
    int total = dp[full * n + order[n - 1]] + 1;
    char *out = malloc((size_t)total + 1);
    strcpy(out, s[order[0]]);
    for (int i = 1; i < n; i++)
        strcat(out, s[order[i]] + ov[order[i - 1] * n + order[i]]);
    free(ov);
    free(len);
    free(dp);
    free(par);
    free(order);
    return out;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n;
    printf("Enter number of strings: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    char **s = malloc((size_t)n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        s[i] = malloc(1001);
        printf("Enter string %d: ", i + 1);
        if (scanf("%1000s", s[i]) != 1) {
            printf("Invalid input\n");
            return 1;
        }
    }
    int m = remove_contained(s, n);
    printf("Strings after removing contained ones: %d\n", m);
    char *g = greedy_superstring(s, m);
    printf("Greedy superstring: %s\n", g);
    printf("Greedy length: %d\n", (int)strlen(g));
    if (m <= 16) {
        char *o = optimal_superstring(s, m);
        printf("Optimal superstring: %s\n", o);
        printf("Optimal length: %d\n", (int)strlen(o));
        printf("Greedy / optimal ratio: %.4f\n", (double)strlen(g) / (double)strlen(o));
        free(o);
    } else {
        printf("Optimal search skipped (more than 16 strings)\n");
    }
    free(g);
    return 0;
}
