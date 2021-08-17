#include <cstdio>

int main()
{
    int i;
    long li;
    long long lli;
    char c;
    float f;
    double d;

    if (std::scanf("%d %ld %lld %1c %f %lf", &i, &li, &lli, &c, &f, &d) == 6)
        std::printf("%d\n%ld\n%lld\n%c\n%.2f\n%.5f\n", i, li, lli, c, f, d);
}
