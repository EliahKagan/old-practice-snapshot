#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <math.h>
#include <stdio.h>

static int digit_sum(int k)
{
    enum { b = 10 };

    int sum = 0;
    for (; k != 0; k /= b) sum += k % b;
    return sum;
}

static void update(int *const bestp, int *const best_sump, const int k)
{
    const int sum = digit_sum(k);
    if (sum < *best_sump) return;

    if (sum == *best_sump) {
        if (k < *bestp) *bestp = k;
    }
    else { // sum > *best_sump
        *best_sump = sum;
        *bestp = k;
    }
}

int main(void)
{
    int n = 0;
    (void)scanf("%d", &n);

    int best = n, best_sum = digit_sum(n);

    const int s = (int)sqrt(n);
    if (s * s == n) update(&best, &best_sum, s);

    for (int k = 2; k < s; ++k) {
        if (n % k == 0) {
            update(&best, &best_sum, k);
            update(&best, &best_sum, n / k);
        }
    }

    printf("%d\n", best);
}
