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
    Aux<It> make_aux(const It first, const It last)
    {
        Aux<It> aux;
        const auto len = std::distance(first, last);
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
                acc += distance(left, right);
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
    
    template<typename It>
    Delta<It> mergesort_subrange(Aux<It>& aux, const It first1, const It last2)
    {
        const auto len = std::distance(first1, last2);
        if (len < 2) return 0;
        
        const auto first2 = std::next(first1, len / 2);
        
        auto acc = mergesort_subrange(aux, first1, first2);
        acc += mergesort_subrange(aux, first2, last2);
        acc += merge(aux, first1, first2, last2);
        return acc;
    }
    
    // Mergesorts the range and returns the inversion count.
    template<typename It>
    Delta<It> mergesort(const It first, const It last)
    {
        auto aux = make_aux(first, last);
        return mergesort_subrange(aux, first, last);
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
