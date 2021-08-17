#include <iostream>

namespace {
    void print_range(const int m, const int n, const char* sep)
    {
        if (m > n) std::cout << '\n';
        else {
            std::cout << sep << m;
            print_range(m + 1, n, " ");
        }
    }

    void run_testcases(const int t)
    {
        if (t > 0) {
            auto n = 0;
            std::cin >> n;
            print_range(1, n, "");
            run_testcases(t - 1);
        }
    }
}

int main()
{
    auto t = 0;
    std::cin >> t;
    run_testcases(t);
}
