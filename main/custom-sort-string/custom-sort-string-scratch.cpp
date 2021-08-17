#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

class Solution {
public:
    static string customSortString(const string& s, string t) noexcept;
};

namespace {
    constexpr auto alpha_len = 'z' - 'a' + 1;
    static_assert(alpha_len == 26, "wrong-length alphabet?");
}

string Solution::customSortString(const string& s, string t) noexcept
{
    array<int, alpha_len> indices {}; // 1-based, where 0 means not present
    for (auto i = 0; i != s.size(); ++i) indices[s[i] - 'a'] = i + 1;
    
    sort(begin(t), end(t), [&indices](const char lc, const char rc) noexcept {
        assert('a' <= lc && lc <= 'z');
        assert('a' <= rc && rc <= 'z');
        return indices[lc - 'a'] < indices[rc - 'a'];
    });
    
    return t;
}

int main()
{
	std::cout << Solution::customSortString("cba", "abcd") << '\n';
}
