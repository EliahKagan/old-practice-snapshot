#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include <vector>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0, x = 0, elem = 0, freq = 0;
        std::cin >> n >> x;

        while (n-- > 0) { // consume elements to find xs
            std::cin >> elem;
            if (elem == x) ++freq;
            else if (freq > 0) break; // since the input sequence is sorted
        }

        while (n-- > 0) std::cin >> elem; // discard any remaining elements

        std::cout << (freq == 0 ? -1 : freq) << '\n';
    }
}
