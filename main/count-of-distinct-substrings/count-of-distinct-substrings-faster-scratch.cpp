#include "count-of-distinct-substrings-faster-scratch.h" // #include<bits/stdc++.h>

using namespace std;

int countDistinctSubstring(string s);

int main()
{
 int t,l,i,j;
 int temp;
    cin>>t;
 while(t--){
 string s;
  cin>>s;
  cout<<countDistinctSubstring(s)<<endl;

 }
}


/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

namespace {
    constexpr auto k_lowercase = "abcdefghijklmnopqrstuvwxyz";

    constexpr bool have_contiguous_lowercase(const ptrdiff_t i = 1) noexcept
    {
        return k_lowercase[i] == '\0'
                || (k_lowercase[i] - k_lowercase[i - 1] == 1
                    && have_contiguous_lowercase(i + 1));
    }

    static_assert(have_contiguous_lowercase(),
                  "lower-case letters must be contiguous");

    constexpr size_t k_maxlen {1000u};

    class Trie {
    public:
        int size() const noexcept { return count; }

        void clear() noexcept
        {
            memset(nodes.data(), 0, count * sizeof(Node));
            count = 1;
        }

        void insert(string::const_iterator first,
                    const string::const_iterator last) noexcept
        {
            for (auto cur = 0; first != last; ++first) {
                auto& next = nodes[cur][*first - 'a'];
                if (next == 0) next = count++;
                cur = next;
            }
        }

    private:
        using Node = array<int, 'z' - 'a' + 1>;

        array<Node, k_maxlen * (k_maxlen + 1u) / 2u + 1u> nodes {};

        int count {1};
    };
}

/*You are required to complete this method */
int countDistinctSubstring(string s)
{
    static Trie trie;

    trie.clear();

    const auto last = s.cend();
    for (auto first = s.cbegin(); first != last; ++first)
        trie.insert(first, last);

    return trie.size();
}
