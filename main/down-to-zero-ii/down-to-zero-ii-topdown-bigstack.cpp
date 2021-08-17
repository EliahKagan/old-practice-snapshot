#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <utility>

#include <sys/resource.h>

namespace {
    constexpr auto debug_check_for_overflow = false;
    constexpr auto debug_rlimit_stacksize = true;

    std::unordered_map<int, int> create_steps_to_zero_memo()
    {
        std::unordered_map<int, int> memo;
        
        memo.emplace(0, 0);
        memo.emplace(1, 1);

        return memo;
    }

    int count_steps_to_zero(const int n, std::unordered_map<int, int>& memo)
    {
        const auto p = memo.find(n);
        if (p != memo.end()) return p->second;

        auto acc = std::numeric_limits<int>::max();
        for (auto k = static_cast<int>(std::sqrt(n)); k != 1; --k) {
            if (n % k == 0)
                acc = std::min(acc, count_steps_to_zero(n / k, memo));
        }

        const auto ret = std::min(acc, count_steps_to_zero(n - 1, memo)) + 1;
        memo.emplace(n, ret);
        return ret;
    }

    int realmain()
    {
        std::ios_base::sync_with_stdio(false);

        if (debug_check_for_overflow) {
            constexpr auto nmax = 1000000;

            for (auto i = 0; i <= nmax; ++i) {
                auto m = create_steps_to_zero_memo();

                std::cout << "DEBUG: " << i << ": "
                          << count_steps_to_zero(i, m) << std::endl;
            }
        }

        auto memo = create_steps_to_zero_memo();

        auto q = 0;
        for (std::cin >> q; q > 0; --q) {
            auto n = 0;
            std::cin >> n;
            std::cout << count_steps_to_zero(n, memo) << '\n';
        }

        return EXIT_SUCCESS;
    }

    void die(const char *const s)
    {
        perror(s);
        std::exit(EXIT_FAILURE);
    }

    template<typename RLimit> // (struct rlimit) or (const struct rlimit)
    void rlimit_stack(int(*const fn)(int, RLimit*), RLimit* const rlim)
    {
        if (fn(RLIMIT_STACK, rlim) != 0) die("foo"); // FIXME: change "foo"

        if (debug_rlimit_stacksize) { // FIXME: change "foo" here too
            std::cerr << "foo" << ": debug: rlim_cur=" << rlim->rlim_cur
                      << ", rlim_max=" << rlim->rlim_max << '\n';
        }
    }
}

int main(int, char** argv)
{
    struct rlimit r {};
    rlimit_stack(getrlimit, &r);
    //if (getrlimit(RLIMIT_STACK, &r) != 0) die(argv[0]);

    //if (debug_rlimit_stacksize) {
    //    std::cerr << argv[0] << ": debug: rlim_cur=" << r.rlim_cur
    //              << ", rlim_max=" << r.rlim_max << '\n';
    //}

    r.rlim_cur = 128 * 1024 * 1024; // 128 MiB
    rlimit_stack(setrlimit, static_cast<const struct rlimit*>(&r));
    //if (setrlimit(RLIMIT_STACK, &r) != 0) die(argv[0]);

    if (debug_rlimit_stacksize) {

    }

    return realmain();
}
