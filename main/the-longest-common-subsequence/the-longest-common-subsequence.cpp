#ifdef _MSC_VER
#define NOMINMAX
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace {
    using std::vector;

    template<typename T>
    std::vector<T> get_record(typename vector<T>::size_type count)
    {
        vector<T> seq;
        for (seq.reserve(count); count != 0u; --count) {
            T x {};
            std::cin >> x;
            seq.push_back(x);
        }

        return seq;
    }

    template<typename T>
    void put_record(const vector<T>& seq)
    {
        auto sep = "";
        for (const auto x : seq) {
            std::cout << sep << x;
            sep = " ";
        }

        std::cout << '\n';
    }

    // Finds some longest common subsequence of a and b, by an iterative
    // algorithm similar to the "Iterative LCS" method described in
    // https://www.ics.uci.edu/~eppstein/161/960229.html (Eppstein 1996). See
    // "Bottom up dynamic programming" and "The subsequence itself" sections.
    template<typename T>
    vector<T> longest_common_subsequence(
            const vector<T>& a, const typename vector<T>::size_type n,
            const vector<T>& b, const typename vector<T>::size_type m)
    {
        assert(a.size() == n && b.size() == m);

        using std::max;
        using Size = typename vector<T>::size_type;
        
        vector<vector<Size>> v (n + 1u, vector<Size>(m + 1u, 0u));
        for (auto i = n; i-- != 0u; ) {
            for (auto j = m; j-- != 0u; ) {
                v[i][j] = (a[i] == b[j] ? 1u + v[i + 1u][j + 1u]
                                        : max(v[i + 1u][j], v[i][j + 1u]));
            }
        }

        vector<T> s;
        s.reserve(v[0u][0u]);
        for (Size i {0u}, j {0u}; i != n && j != m; ) {
            if (a[i] == b[j]) {
                s.push_back(a[i++]);
                ++j;
            }
            else if (v[i + 1u][j] < v[i][j + 1u]) ++j;
            else ++i;
        }

        return s;
    }
}

int main()
{
    vector<int>::size_type n {}, m{};
    std::cin >> n >> m;

    const auto a = get_record<int>(n), b = get_record<int>(m);
    put_record(longest_common_subsequence(a, n, b, m));
}
