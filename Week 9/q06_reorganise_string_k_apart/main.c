#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cnt;
    unsigned char ch;
} Entry;

static int better(Entry a, Entry b)
{
    return a.cnt > b.cnt || (a.cnt == b.cnt && a.ch < b.ch);
}

static void sift_up(Entry *h, int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!better(h[i], h[p]))
            break;
        Entry t = h[i];
        h[i] = h[p];
        h[p] = t;
        i = p;
    }
}

static void sift_down(Entry *h, int n, int i)
{
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < n && better(h[l], h[m]))
            m = l;
        if (r < n && better(h[r], h[m]))
            m = r;
        if (m == i)
            break;
        Entry t = h[i];
        h[i] = h[m];
        h[m] = t;
        i = m;
    }
}

char *reorganise(const char *s, int k)
{
    int n = (int)strlen(s);
    char *out = malloc((size_t)n + 1);
    if (k <= 1) {
        strcpy(out, s);
        return out;
    }
    int count[256] = {0};
    for (int i = 0; i < n; i++)
        count[(unsigned char)s[i]]++;
    Entry heap[256];
    int hs = 0;
    for (int c = 0; c < 256; c++) {
        if (count[c] > 0) {
            heap[hs].cnt = count[c];
            heap[hs].ch = (unsigned char)c;
            sift_up(heap, hs++);
        }
    }
    Entry *wait = malloc((size_t)(n + 1) * sizeof(Entry));
    int head = 0, tail = 0;
    for (int i = 0; i < n; i++) {
        if (hs == 0) {
            free(out);
            free(wait);
            return NULL;
        }
        Entry e = heap[0];
        heap[0] = heap[--hs];
        sift_down(heap, hs, 0);
        out[i] = (char)e.ch;
        e.cnt--;
        wait[tail++] = e;
        if (tail - head >= k) {
            Entry r = wait[head++];
            if (r.cnt > 0) {
                heap[hs] = r;
                sift_up(heap, hs++);
            }
        }
    }
    out[n] = '\0';
    free(wait);
    return out;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    static char s[1000001];
    int k;
    printf("Enter string S: ");
    if (scanf("%1000000s", s) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter K: ");
    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Invalid input\n");
        return 1;
    }
    char *res = reorganise(s, k);
    if (res == NULL) {
        printf("Result: \"\" (not possible)\n");
    } else {
        printf("Result: %s\n", res);
        free(res);
    }
    return 0;
}
