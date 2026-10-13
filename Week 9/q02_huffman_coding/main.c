#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long long *Fq;

static int less_node(int a, int b)
{
    return Fq[a] < Fq[b] || (Fq[a] == Fq[b] && a < b);
}

static void sift_up(int *h, int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!less_node(h[i], h[p]))
            break;
        int t = h[i];
        h[i] = h[p];
        h[p] = t;
        i = p;
    }
}

static void sift_down(int *h, int n, int i)
{
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < n && less_node(h[l], h[m]))
            m = l;
        if (r < n && less_node(h[r], h[m]))
            m = r;
        if (m == i)
            break;
        int t = h[i];
        h[i] = h[m];
        h[m] = t;
        i = m;
    }
}

void huffman_lengths(const long long *f, int n, int *len)
{
    if (n == 1) {
        len[0] = 1;
        return;
    }
    int total = 2 * n - 1;
    Fq = malloc((size_t)total * sizeof(long long));
    int *parent = malloc((size_t)total * sizeof(int));
    int *depth = calloc((size_t)total, sizeof(int));
    int *heap = malloc((size_t)n * sizeof(int));
    int hs = 0;
    for (int i = 0; i < n; i++) {
        Fq[i] = f[i];
        parent[i] = -1;
        heap[hs] = i;
        sift_up(heap, hs++);
    }
    int next = n;
    while (hs > 1) {
        int a = heap[0];
        heap[0] = heap[--hs];
        sift_down(heap, hs, 0);
        int b = heap[0];
        heap[0] = heap[--hs];
        sift_down(heap, hs, 0);
        Fq[next] = Fq[a] + Fq[b];
        parent[a] = parent[b] = next;
        parent[next] = -1;
        heap[hs] = next;
        sift_up(heap, hs++);
        next++;
    }
    for (int i = next - 2; i >= 0; i--)
        depth[i] = depth[parent[i]] + 1;
    for (int i = 0; i < n; i++)
        len[i] = depth[i];
    free(Fq);
    free(parent);
    free(depth);
    free(heap);
}

static const int *SL;
static const char *SS;

static int cmp_canonical(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    if (SL[x] != SL[y])
        return SL[x] - SL[y];
    return (unsigned char)SS[x] - (unsigned char)SS[y];
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n;
    printf("Enter number of symbols: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    char *sym = malloc((size_t)n);
    long long *f = malloc((size_t)n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        printf("Enter symbol and frequency %d: ", i + 1);
        if (scanf(" %c %lld", &sym[i], &f[i]) != 2 || f[i] <= 0) {
            printf("Invalid input\n");
            return 1;
        }
    }
    int *len = malloc((size_t)n * sizeof(int));
    huffman_lengths(f, n, len);
    int *order = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++)
        order[i] = i;
    SL = len;
    SS = sym;
    qsort(order, (size_t)n, sizeof(int), cmp_canonical);
    int maxlen = len[order[n - 1]];
    char *code = malloc((size_t)maxlen + 2);
    int cl = len[order[0]];
    memset(code, '0', (size_t)cl);
    code[cl] = '\0';
    long long weighted = 0, sum = 0;
    printf("Canonical Huffman codebook:\n");
    printf("  Symbol  Freq  Length  Code\n");
    for (int k = 0; k < n; k++) {
        int i = order[k];
        if (k > 0) {
            int p = cl - 1;
            while (p >= 0 && code[p] == '1')
                code[p--] = '0';
            if (p >= 0)
                code[p] = '1';
            while (cl < len[i])
                code[cl++] = '0';
            code[cl] = '\0';
        }
        printf("  %-6c  %-4lld  %-6d  %s\n", sym[i], f[i], len[i], code);
        weighted += f[i] * len[i];
        sum += f[i];
    }
    printf("Total weighted length: %lld\n", weighted);
    printf("Expected code length: %.4f bits/symbol\n", (double)weighted / (double)sum);
    free(sym);
    free(f);
    free(len);
    free(order);
    free(code);
    return 0;
}
