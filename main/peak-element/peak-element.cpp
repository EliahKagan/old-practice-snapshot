#include "peak-element.h" //#include<bits/stdc++.h>
using namespace std;


int peak(int arr[], int n);
int main() {
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a (n); //int a[n];
        for (int i = 0; i<n; i++)
        {
            cin >> a[i];
        }
        bool f = 0;
        int A = peak(a.data(), n);

        if (n == 1)
            f = 1;
        else
            if (A == 0 and a[0] >= a[1])
                f = 1;
            else if (A == n - 1 and a[n - 1] >= a[1])
                f = 1;
            else if (a[A] >= a[A + 1] and a[A] >= a[A - 1])
                f = 1;
            else
                f = 0;

        cout << f << endl;

    }
    // your code goes here
    return 0;
}

/* The function should return the index of any
   peak element present in the array */

int peak(int arr[], int n)
{
    if (n <= 0) throw out_of_range{"the array must have at least one element"};
    
    if (n == 1 || arr[0] >= arr[1]) return 0;

    for (auto i = 1; i != n - 1; ++i)
        if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1]) return i;
    
    assert(arr[n - 1] >= arr[n - 2]);
    return n - 1;
}
