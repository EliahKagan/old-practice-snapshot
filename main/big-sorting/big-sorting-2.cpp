#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace {
    std::vector<std::string> read_bignums()
    {
        int n {};
        std::cin >> n;

        std::vector<std::string> a (n);
        std::copy_n(std::istream_iterator<std::string>{std::cin}, n,
                    begin(a));

        return a;
    }

    void sort_bignums(std::vector<std::string>& a) noexcept
    {
        std::sort(begin(a), end(a), [](const std::string& lhs,
                                       const std::string& rhs) noexcept {
            return lhs.size() != rhs.size() ? lhs.size() < rhs.size()
                                            : lhs < rhs;
        });
    }

    void print_bignums(const std::vector<std::string>& a) noexcept
    {
        std::copy(begin(a), end(a),
                  std::ostream_iterator<std::string>{std::cout, "\n"});
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto a = read_bignums();
    sort_bignums(a);
    print_bignums(a);
}
