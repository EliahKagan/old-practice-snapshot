#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        uint32_t n  = 0u;
        (void)scanf("%" SCNu32, &n);
        printf("%" PRIu32 "\n", ~n);
    }
    
    return 0;
}
