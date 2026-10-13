#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

static void sift_up(ll *h, int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h[i] >= h[p])
            break;
        ll t = h[i];
        h[i] = h[p];
        h[p] = t;
        i = p;
    }
}

static void sift_down(ll *h, int n, int i)
{
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < n && h[l] < h[m])
            m = l;
        if (r < n && h[r] < h[m])
            m = r;
        if (m == i)
            break;
        ll t = h[i];
        h[i] = h[m];
        h[m] = t;
        i = m;
    }
}

static ll pop_min(ll *h, int *hs)
{
    ll top = h[0];
    h[0] = h[--(*hs)];
    sift_down(h, *hs, 0);
    return top;
}

ll connect_sticks(const ll *L, int n, int verbose)
{
    ll *h = malloc((size_t)n * sizeof(ll));
    int hs = 0;
    for (int i = 0; i < n; i++) {
        h[hs] = L[i];
        sift_up(h, hs++);
    }
    ll cost = 0;
    while (hs > 1) {
        ll a = pop_min(h, &hs);
        ll b = pop_min(h, &hs);
        cost += a + b;
        if (verbose)
            printf("  connect %lld + %lld = %lld (cost so far %lld)\n", a, b, a + b, cost);
        h[hs] = a + b;
        sift_up(h, hs++);
    }
    free(h);
    return cost;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n;
    printf("Enter number of sticks: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    ll *L = malloc((size_t)n * sizeof(ll));
    printf("Enter %d stick lengths: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &L[i]) != 1 || L[i] <= 0) {
            printf("Invalid input\n");
            return 1;
        }
    }
    printf("Steps:\n");
    ll cost = connect_sticks(L, n, 1);
    printf("Minimum total cost: %lld\n", cost);
    free(L);
    return 0;
}
