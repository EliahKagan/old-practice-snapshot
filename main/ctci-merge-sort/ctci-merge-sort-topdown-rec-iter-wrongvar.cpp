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
    
    enum class Action { go_left, go_right, retreat };
    
    template<typename It>
    struct Frame {
        constexpr Frame(const It _first, const It _last) noexcept
            : first{_first}, last{_last} { }
    
        It first, last;
        Action action {Action::go_left};
    };
    
    // Iteratively implemented recursive top-down mergesort. Counts inversions.
    template<typename It>
    Delta<It> mergesort(const It first, const It last)
    {
        if (!maybe_unsorted(first, last)) return 0;
        
        Delta<It> acc {};
        auto aux = make_aux(first, last);
        
        std::stack<Frame<It>> frames;
        frames.emplace(first, last);
        
        while (!frames.empty()) {
            auto& frame = frames.top();
            
            switch (frame.action) {
            case Action::go_left:
                {
                    frame.action = Action::go_right;
                    const auto mid = midpoint(frame.first, frame.last);
                    if (maybe_unsorted(first, mid)) frames.emplace(first, mid);
                    break;
                }

            case Action::go_right:
                {
                    frame.action = Action::retreat;
                    const auto mid = midpoint(frame.first, frame.last);
                    if (maybe_unsorted(mid, last)) frames.emplace(mid, last);
                    break;
                }

            case Action::retreat:
                {
                    const auto mid = midpoint(frame.first, frame.last);
                    acc += merge(aux, frame.first, mid, frame.last);
                    frames.pop();
                    break;
                }
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
