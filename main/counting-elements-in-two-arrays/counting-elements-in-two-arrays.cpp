// C++ implementation of For each element in 1st 
// array count elements less than or equal to it
// in 2nd array
#include "counting-elements-in-two-arrays.h" //#include <bits/stdc++.h>

using namespace std;

// function returns the index of largest element 
// smaller than equal to 'x' in 'arr'. For duplicates
// it returns the last index of occurrence of required
// element. If no such element exits then it returns -1. 
int binary_search(int arr[], int l, int h, int x);

// function to count for each element in 1st array,
// elements less than or equal to it in 2nd array
void countEleLessThanOrEqual(int arr1[], int arr2[],
    int m, int n);

// Driver program to test above
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int m, n;
        cin >> m >> n;
        vector<int> arr1 (m), arr2 (n); //int arr1[m], arr2[n];
        for (int i = 0; i<m; i++)
            cin >> arr1[i];
        for (int j = 0; j<n; j++)
            cin >> arr2[j];
        countEleLessThanOrEqual(arr1.data(), arr2.data(), m, n); // added .data()
        cout << endl;
    }
    return 0;
}

namespace {
    // Returns the last index to an element less than or equal to key,
    // in range a[low..high], or low if there is no such element.
    int find_last_not_greater(int *const a, const int low, const int high,
                              const int key)
    {
        if (low >= high) return low;
        
        const auto mid = (low + high + 1) / 2;
        
        return a[mid] > key ? find_last_not_greater(a, low, mid - 1, key)
                            : find_last_not_greater(a, mid, high, key);
    }
}

// Returns the index of largest element less than or equal to key in
// a[low..high]. For duplicates, returns the highest index to key.
// If all elements are greater than key, returns -1.
int binary_search(int *const a, const int low, const int high, const int key)
{
    const auto i = find_last_not_greater(a, low, high, key);
    return a[i] > key ? -1 : i;
}

// function to count for each element in 1st array,
// elements less than or equal to it in 2nd array

// For each element in a, prints the number of elements in b that are less than
// or equal to it.
void countEleLessThanOrEqual(int *const a, int *const b, 
                             const int m, const int n)
{
    std::sort(b, b + n);
    
    for (auto i = 0; i != m; ++i) {
        const auto result = binary_search(b, 0, n - 1, a[i]) + 1;
        assert(result == std::upper_bound(b, b + n, a[i]) - b);
        cout << result << ' ';
    }
}
