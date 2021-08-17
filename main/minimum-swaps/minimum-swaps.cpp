// C++ program to find minimum number of swaps
// required to sort an array
#include "minimum-swaps.h" //#include<bits/stdc++.h>
using namespace std;

int minSwaps(int A[], int N);

// Driver program to test the above function
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a (n); //int a[n];
        for (int i = 0; i<n; i++)
            cin >> a[i];
        cout << minSwaps(a.data(), n) << endl; // added .data() call
    }
}


namespace {
    constexpr auto visited = numeric_limits<size_t>::max();
    
    vector<size_t> normalizeToPermutation(const int* const a, const size_t len)
    {
        vector<size_t> v (len);
        const auto p = begin(v), q = end(v);
        
        iota(p, q, static_cast<size_t>(0u));
        
        sort(p, q, [a](const size_t i, const size_t j) {
            return a[i] < a[j];
        });
        
        return v;
    }
    
    // Traverses the cycle of the permutation v that begins at index start,
    // marking each element visited and returning the number of positions
    // traversed (always at least 1).
    int traverseAndMarkCycle(vector<size_t>& v, const size_t start)
    {
        int cycleLength = 0;
        
        auto cur = start;
        do {
            ++cycleLength;
            const auto next = v[cur];
            v[cur] = visited;
            cur = next;
        }
        while (cur != start);
        
        return cycleLength;
    }
}

/* You are required to complete this method */
int minSwaps(int* const a, const int n)
{
    const auto len = static_cast<size_t>(n);
    auto v = normalizeToPermutation(a, len);
    
    auto swaps = 0;
    for (size_t i = 0u; i != len; ++i)
        if (v[i] != visited) swaps += traverseAndMarkCycle(v, i) - 1;
    
    return swaps;
}
