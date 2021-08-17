#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>

namespace {
    // Naive algorithm to determine the representation length of n in base b.
    // (Assumes n > 0.) This is possibly fast enough for the current purpose,
    // given the problem's modest constraints.
    inline int representation_length(int n, const int b)
    {
        auto len = 0;
        for (; n != 0; n /= b) ++len;
        return len;
    }

    // Checks if n > 0 has a representation length of k in any base.
    // Returns true if it does (i.e., if such a base is found).
    bool has_representation_length(const int n, const int k)
    {
        assert(n > 0);
        
        for (auto b = 2; ; ++b) {
            const auto len = representation_length(n, b);
            if (len <= k) return len == k;
        }
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t >0; --t) {
        auto n = 0, k = 0;
        std::cin >> n >> k;
        std::cout << (has_representation_length(n, k) ? "YES" : "NO") << '\n';
    }
}
