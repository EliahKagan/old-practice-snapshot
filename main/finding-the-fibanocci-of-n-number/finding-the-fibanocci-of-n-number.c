#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    for (int n; scanf("%d", &n) == 1; ) {
        putchar('0');

        for (uintmax_t a = 0u, b = 1u; n > 0; --n) {
            const uintmax_t tmp = a;
            a = b;
            b += tmp;

            // The problem statement and example input/output are ambiguous and
            // seemingly contradictory. Let's try stringing the numerals of
            // each element together with no delimiting whitespace (which
            // appears to be the desired method, based on a sample test case).
            printf("%" PRIuMAX, b);
        }

        putchar('\n');
    }
}
