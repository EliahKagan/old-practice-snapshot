#include <cassert>
#include <cstddef>
#include <vector>
#include <iostream>
#include <iterator>
#include <stdexcept>

namespace {
    int check_size_and_get_square(const int size) // helper for read_record()
    {
        if (size < 0) throw std::out_of_range{"size must be nonnegative"};

        const auto square = size * size;

        if (square < 0 || square / size != size)
            throw std::out_of_range{"size too big"};

        return square;
    }

    std::vector<int> read_record(const int size)
    {
        const auto square = check_size_and_get_square(size);
        
        std::vector<int> values (static_cast<std::size_t>(size));
        
        for (auto& x : values) {
            std::cin >> x;
            if (x >= square) throw std::out_of_range{"element too big"};
        }
        
        return values;
    }
    
    void print(const std::vector<int>& values)
    {
        auto sep = "";
        for (const auto x : values) {
            std::cout << sep << x;
            sep = " ";
        }
        
        std::cout << '\n';
    }
    
    template<class TFunc> // helper function for counting_sort()
    std::vector<std::vector<int>> counting_sort_bins(
            const std::vector<int>& values, const std::size_t key_range,
                                            const TFunc key_selector)
    {
        std::vector<std::vector<int>> bins (key_range);
        for (const auto x : values) bins[key_selector(x)].push_back(x);
        return bins;
    }
    
    template<class TFunc>
    void counting_sort(std::vector<int>& values, const std::size_t key_range,
                       const TFunc key_selector)
    {
        const auto bins = counting_sort_bins(values, key_range, key_selector);
        auto p = std::begin(values);
        
        for (const auto& bin : bins) {
            for (const auto x : bin) {
                *p = x;
                ++p;
            }
        }
        
        assert(p == std::end(values));
    }
    
    // assumes every element of values is strictly less than radix * radix
    void radix_sort(std::vector<int>& values, const int radix)
    {
        assert(radix > 0);
        const auto key_range = static_cast<std::size_t>(radix);
        
        counting_sort(values, key_range, [radix](const int x) {
            return static_cast<std::size_t>(x % radix);
        });
        
        counting_sort(values, key_range, [radix](const int x) {
            return static_cast<std::size_t>(x / radix);
        });
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto size = 0;
        std::cin >> size;
        
        auto values = read_record(size);
        radix_sort(values, size * size);
        print(values);
    }
}
