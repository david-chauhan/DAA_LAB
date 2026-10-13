#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long d, f;
} Station;

static int cmp_dist(const void *a, const void *b)
{
    const Station *x = a, *y = b;
    return (x->d > y->d) - (x->d < y->d);
}

static void sift_up(Station *h, int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h[i].f <= h[p].f)
            break;
        Station t = h[i];
        h[i] = h[p];
        h[p] = t;
        i = p;
    }
}

static void sift_down(Station *h, int n, int i)
{
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < n && h[l].f > h[m].f)
            m = l;
        if (r < n && h[r].f > h[m].f)
            m = r;
        if (m == i)
            break;
        Station t = h[i];
        h[i] = h[m];
        h[m] = t;
        i = m;
    }
}

int min_stops(long long D, long long F, Station *s, int n, long long *used)
{
    qsort(s, (size_t)n, sizeof(Station), cmp_dist);
    Station *heap = malloc((size_t)(n + 1) * sizeof(Station));
    int hs = 0, i = 0, stops = 0;
    long long reach = F;
    while (reach < D) {
        while (i < n && s[i].d <= reach) {
            heap[hs] = s[i++];
            sift_up(heap, hs++);
        }
        if (hs == 0) {
            free(heap);
            return -1;
        }
        Station top = heap[0];
        heap[0] = heap[--hs];
        sift_down(heap, hs, 0);
        reach += top.f;
        if (used)
            used[stops] = top.d;
        stops++;
    }
    free(heap);
    return stops;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    long long D, F;
    int n;
    printf("Enter target distance D and initial fuel F: ");
    if (scanf("%lld %lld", &D, &F) != 2 || D < 0 || F < 0) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter number of stations: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input\n");
        return 1;
    }
    Station *s = malloc((size_t)(n + 1) * sizeof(Station));
    for (int i = 0; i < n; i++) {
        printf("Enter distance and fuel of station %d: ", i + 1);
        if (scanf("%lld %lld", &s[i].d, &s[i].f) != 2 || s[i].d < 0 || s[i].f < 0) {
            printf("Invalid input\n");
            return 1;
        }
    }
    long long *used = malloc((size_t)(n + 1) * sizeof(long long));
    int stops = min_stops(D, F, s, n, used);
    if (stops < 0) {
        printf("Cannot reach the target\n");
    } else {
        printf("Minimum number of refuelling stops: %d\n", stops);
        printf("Refuel at distances:");
        for (int i = 0; i < stops; i++)
            printf(" %lld", used[i]);
        printf("\n");
    }
    free(s);
    free(used);
    return 0;
}
