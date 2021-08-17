#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    template<typename It>
    using Delta = typename std::iterator_traits<It>::difference_type;
    
    template<typename It>
    using Aux = std::vector<typename std::iterator_traits<It>::value_type>;
    
    template<typename It>
    Aux<It> make_aux(const Delta<It> len)
    {
        Aux<It> aux;
        aux.reserve(static_cast<typename Aux<It>::size_type>(len));
        return aux;
    }
    
    template<typename It>
    Delta<It> merge(Aux<It>& aux, const It first1, // last1 is first2
                                  const It first2, const It last2)
    {
        assert(aux.empty());
        Delta<It> acc {};
        auto left = first1, right = first2;
        
        // Merge elements until (at least) one side is used up.
        while (left != first2 && right != last2) {
            if (*right < *left) {
                acc += distance(left, first2);
                aux.push_back(std::move(*right));
                ++right;
            } else {
                aux.push_back(std::move(*left));
                ++left;
            }
        }
        
        // Move the remaining elements from whichever side has them.
        std::move(left, first2, back_inserter(aux));
        std::move(right, last2, back_inserter(aux));
        
        // Move everything back from auxiliary storage to the original range.
        const auto d_last = std::move(begin(aux), end(aux), first1);
        assert(d_last == last2);
        aux.clear();
        
        return acc;
    }
    
    // Mergesorts the range (bottom-up) and returns the inversion count.
    template<typename It>
    Delta<It> mergesort(const It first, const It last)
    {
        const auto len = std::distance(first, last);
        auto aux = make_aux<It>(len);
        Delta<It> acc {};
        
        for (Delta<It> delta {1}; delta < len; delta *= 2) {
            for (Delta<It> start1 {0}; ; ) {
                const auto start2 = start1 + delta;
                if (start2 >= len) break;
                
                const auto stop2 = std::min(start2 + delta, len);
                
                acc += merge(aux, std::next(first, start1),
                                  std::next(first, start2),
                                  std::next(first, stop2));
                
                start1 = stop2;
            }
        }
        
        return acc;
    }
    
    std::vector<int> read_record()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::vector<int> a (n);
        for (auto& x : a) std::cin >> x;
        return a;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int t {};
    for (std::cin >> t; t > 0; --t) {
        auto a = read_record();
        std::cout << mergesort(begin(a), end(a)) << '\n';
    }
}
