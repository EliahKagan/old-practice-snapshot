#include <complex>
#include <iostream>
#include <vector>

namespace {
    std::vector<long long> get_record()
    {
        constexpr std::vector<long long>::size_type size{ 5u };

        std::vector<long long> a;
        a.reserve(size);

        for (auto i = size; i != 0u; --i) {
            auto x = 0LL;
            std::cin >> x;
            a.push_back(x);
        }

        return a;
    }

    std::complex<long long> product(const std::vector<long long>& reals,
                                    const std::vector<long long>& imags)
    {
        std::complex<long long> acc {1LL, 0LL};

        const auto endp = reals.cend();
        for (auto re = reals.cbegin(), im = imags.cbegin(); re != endp;
                                                            ++re, ++im)
            acc *= std::complex<long long>{*re, *im};

        return acc;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto reals = get_record(), imags = get_record();
        const auto z = product(reals, imags);
        std::cout << z.real() << ' ' << z.imag() << '\n';
    }
}
