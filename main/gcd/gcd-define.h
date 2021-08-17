#ifndef GCD_DEFINE_H_
#define GCD_DEFINE_H_

namespace {
    int gcd(int m, int n) noexcept
    {
        while (n != 0) {
            const auto tmp = n;
            n = m % n;
            m = tmp;
        }

        return m;
    }
}

#endif // ! GCD_DEFINE_H_
