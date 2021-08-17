#include <cctype>
#include <iostream>
#include <iterator>
#include <string>

namespace {
    template<typename It, typename Pred>
    bool selected_are_palindrome(It first, It last, const Pred predicate)
    {
        if (first == last) return true;

        for (--last; first < last; ) {
            if (!predicate(*first)) {
                ++first;
            } else if (!predicate(*last)) {
                --last;
            } else if (*first != *last) {
                return false;
            } else {
                ++first;
                --last;
            }
        }

        return true;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << std::boolalpha;

    const auto not_blank = [](const char ch) {
        return !std::isblank(static_cast<unsigned char>(ch));
    };

    for (std::string s; std::getline(std::cin, s) && !s.empty(); ) {
        std::cout << selected_are_palindrome(std::cbegin(s), std::cend(s),
                                             not_blank)
                  << '\n';
    }
}
