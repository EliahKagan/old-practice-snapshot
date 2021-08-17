#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <stack>
#include <tuple>
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
    constexpr bool maybe_unsorted(It first, const It last) noexcept
    {
        return first != last && ++first != last;
    }
    
    template<typename It>
    constexpr It midpoint(It first, const It last) noexcept
    {
        std::advance(first, std::distance(first, last) / 2);
        return first;
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
    
    // Mergesorts range (top-down, iterative) and returns the inversion count.
    template<typename It>
    Delta<It> mergesort(It first, It last)
    {
        Delta<It> acc {};
        auto aux = make_aux(first, last);
        auto post_first = last, post_last = last;
        
        for (std::stack<std::tuple<It, It>> intervals;
                maybe_unsorted(first, last) || !intervals.empty(); ) {
            // Traverse left as far as possible.
            for (; maybe_unsorted(first, last); last = midpoint(first, last))
                intervals.emplace(first, last);
            
            It first1 {}, last2 {};
            std::tie(first1, last2) = intervals.top();
            const auto first2 = midpoint(first1, last2);
            
            if (maybe_unsorted(first2, last2)
                    && (first2 != post_first || last2 != post_last)) {
                // The right subtree is nonempty and unvisited, so visit it.
                first = first2;
                last = last2;
            } else {
                // We have done any tasks in the right subtree. Retreat.
                acc += merge(aux, first1, first2, last2);
                post_first = first1;
                post_last = last2;
                intervals.pop();
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
