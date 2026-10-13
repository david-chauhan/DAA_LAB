#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

static void sift_up(ll *h, int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h[i] <= h[p])
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
        if (l < n && h[l] > h[m])
            m = l;
        if (r < n && h[r] > h[m])
            m = r;
        if (m == i)
            break;
        ll t = h[i];
        h[i] = h[m];
        h[m] = t;
        i = m;
    }
}

ll minimise_deviation(const ll *a, int n)
{
    ll *h = malloc((size_t)n * sizeof(ll));
    int hs = 0;
    ll mn = -1;
    for (int i = 0; i < n; i++) {
        ll x = a[i] % 2 ? a[i] * 2 : a[i];
        if (mn < 0 || x < mn)
            mn = x;
        h[hs] = x;
        sift_up(h, hs++);
    }
    ll best = h[0] - mn;
    for (;;) {
        ll mx = h[0];
        if (mx - mn < best)
            best = mx - mn;
        if (mx % 2)
            break;
        mx /= 2;
        if (mx < mn)
            mn = mx;
        h[0] = mx;
        sift_down(h, hs, 0);
    }
    free(h);
    return best;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    ll *a = malloc((size_t)n * sizeof(ll));
    printf("Enter %d positive integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &a[i]) != 1 || a[i] <= 0) {
            printf("Invalid input\n");
            return 1;
        }
    }
    printf("Minimum deviation: %lld\n", minimise_deviation(a, n));
    free(a);
    return 0;
}
