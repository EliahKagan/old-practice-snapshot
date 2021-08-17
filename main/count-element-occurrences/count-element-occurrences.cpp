// A C++ program to print elements with count more than n/k
// Modified from original geeksforgeeks.org boilerplate source code:
//  (a) Added comments.
//  (b) Line numbering unfortunately changed (due to added code and comments).
//  (c) Improved indentation for readability.
//  (d) Used vector instead of VLA for compatibility: VLAs aren't standard C++.
//  (e) Added my solution to the end.
#include<iostream>
#include<vector>
using namespace std;
long long int totalcount = 0;

void moreThanNdK(long long int arr[], long long int n, long long int k);

// A structure to store an element and its current count
struct eleCount
{
    long long int e;  // Element
    long long int c;  // Count
};

/* Driver program to test above function */
int main()
{
    long long int t, k;
    cin >> t;
    while (t--)
    {
        long long int n, i;
        cin >> n;
        vector<long long> arr (n); //long long int arr[n];
        for (i = 0; i<n; i++)
            cin >> arr[i];
        cin >> k;
        moreThanNdK(arr.data(), n, k);
        totalcount = 0;
    }
    return 0;
}

// A structure to store an element and its current count
/* struct eleCount
{
    long long int e;  // Element
    long long int c;  // Count
};
*/

namespace { // I assume each a[i] <= n (not just <= nmax). O(1) extra space.
    constexpr auto shift = 32u;
    constexpr auto value_mask = static_cast<long long>(~(~0uLL << shift));
    
    inline long long extract_value(const long long cell)
    {
        return cell & value_mask;
    }

    inline long long extract_count(const long long cell)
    {
        return cell >> shift; // note: assumes high-order bit is 0
    }
    
    inline void insert_count(long long& cell, const long long count)
    {
        cell = (cell & value_mask) | (count << shift);
    }
    
    inline long long get_count(long long* const a, const long long value)
    {
        return extract_count(a[value - 1LL]);
    }
    
    inline void set_count(long long* const a, const long long value,
                                              const long long count)
    {
        insert_count(a[value - 1LL], count);
    }
    
    inline long long increment_count(long long* const a, const long long value)
    {
        const auto count = get_count(a, value) + 1LL;
        set_count(a, value, count);
        return count;
    }
}

// Prints elements with more than n/k occurrences in a[] of
// size n. If there are no such elements, then it prints nothing.
// FIXME: This comment seems incorrect.
void moreThanNdK(long long* const a, const long long n, const long long k)
{
    const auto threshold = n / k + 1LL;
    
    auto acc = 0;
    for (auto i = 0LL; i != n; ++i)
        if (increment_count(a, extract_value(a[i])) == threshold) ++acc;
    
    cout << acc << '\n';
}
