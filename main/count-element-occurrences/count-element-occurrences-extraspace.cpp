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

// Prints elements with more than n/k occurrences in values[] of
// size n. If there are no such elements, then it prints nothing.
// FIXME: This comment seems incorrect.
void moreThanNdK(long long* const values, const long long n, const long long k)
{
    // I assume only each a[i] <= nmax. Uses "O(n)" (nmax) extra space.
    static constexpr auto nmax = 100000LL;
    static int counts[nmax + 1LL] {};
    static int* used[nmax] {}; // stack of pointers to nonzero counts

    const auto threshold = n / k + 1LL;

    auto top = used;
    auto acc = 0;
    
    for (auto i = 0LL; i != n; ++i) {
        auto& c {counts[values[i]]};
        if (c == 0) *top++ = &c;
        if (++c == threshold) ++acc;
    }

    while (top != used) **--top = 0;
    cout << acc << '\n';
}
