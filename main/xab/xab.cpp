#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#endif

#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <cstdio>

int main()
{
    constexpr auto min = 1, max = 1000;

    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        auto a = 0, b = 0;
        (void)std::scanf(" x + %d = %d", &a, &b);
        assert(min <= a && a <= max && min <= b && b <= max);
        std::printf("%d\n", b - a);
    }
}
