#include <cstddef>
#include <iomanip>
#include <iostream>
#include <functional>
#include <unordered_set>

namespace {
    // In real life, consider std::tuple<T, T> or std::pair<T, T> instead.
    template<typename T>
    struct MyPair {
        T first, second;

        constexpr MyPair() : first{}, second{} { }
        constexpr MyPair(const T& fst, const T& snd) : first{fst}, second{snd} { }
    };

    template<typename T>
    constexpr bool operator==(const MyPair<T>& lhs, const MyPair<T>& rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<typename T>
    constexpr bool operator!=(const MyPair<T>& lhs, const MyPair<T>& rhs)
    {
        return !(lhs == rhs);
    }
    
    template<typename T>
    constexpr double ratio(const T& x, const T& y)
    {
        return static_cast<double>(x) / static_cast<double>(y);
    }
}

namespace std {
    template<typename T>
    struct hash<MyPair<T>> {
        std::size_t operator()(const MyPair<T>& v) const
        {
            // See rationale at https://stackoverflow.com/a/2816747 by
            // https://stackoverflow.com/users/21499/dr-hans-peter-störr.
            // Note that this is a somewhat different use case because the
            // values being multiplied here are themselves hash codes, possibly
            // generated in a similar way, and because Störr's testing was with
            // a Java virtual machines. If this yields more hash collisions
            // than expected, blame me, not him!
            static constexpr std::size_t hashing_multiplier{92'821};
            return m_hash(v.first) ^ m_hash(v.second) * hashing_multiplier;
        }

    private:
        const hash<T> m_hash {};
    };
}

int main()
{
    constexpr auto r = 1000; // Manhattan metric

    std::unordered_set<MyPair<int>> pairs;
    std::unordered_set<std::size_t> codes;

    const std::hash<MyPair<int>> hasher;

    for (auto i = -r; i <= r; ++i) {
        for (auto j = -r; j <= r; ++j) {
            const MyPair<int> ij {i, j};
            pairs.insert(ij);
            codes.insert(hasher(ij));
        }
    }

    const auto npairs = pairs.size();
    const auto ncodes = codes.size();
    const auto mean_pairs_per_code = ratio(npairs, ncodes);

    std::cout << "pairs.size() = " << npairs << '\n';
    std::cout << "codes.size() = " << ncodes << '\n';

    std::cout << "On average (NOT what matters most) ~" << std::setprecision(3)
            << std::fixed << mean_pairs_per_code << " values share a code.\n";
}
