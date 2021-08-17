#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t reverse_bits(uint32_t bits)
{
    uint32_t ret = 0u;
    
    for (; bits != 0u; bits >>= 1) {
        ret <<= 1;
        ret |= (bits & 1);
    }

    return ret;
}

int main(void)
{
    for (uint32_t bits; scanf("%" SCNu32, &bits) == 1; )
        printf("%" PRIu32 "\n", reverse_bits(bits));
}
