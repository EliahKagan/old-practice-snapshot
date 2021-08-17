#include "find-duplicates-in-an-array.h" //#include <bits/stdc++.h>
using namespace std;
void printDuplicates(int arr[], int n);
int main()
{
  int t;
  cin>>t;
  while(t-- > 0){
		int n;
		cin>>n;
        vector<int> a (n);  //int a[n];
		for(int i=0;i<n;i++)
			cin>>a[i];
        printDuplicates(a.data(), n); //printDuplicates(a, n);
		cout<<endl;
  }
  return 0;
}

namespace { // This version outputs values eagerly (when it finds the second).
    constexpr auto debug_check_element = false;

    enum History {
        not_seen = 0,
        seen_once = 1 << 29,
        seen_twice = seen_once << 1,
        clear_history = ~(seen_once | seen_twice)
    };
    
    void check_n(const int n)
    {
        if (n < 0) throw out_of_range{"n must be nonnegative"};
        if (n >= seen_once) throw out_of_range{"n is too big"};
    }
    
    inline void check_element(const int n, const int elem)
    {
        if (debug_check_element) {
            cerr << "DEBUG: check_element: n=" << n
                 << " elem=" << elem << '\n';
        }

        if (elem < 0) throw out_of_range{"element must be nonnegative"};
        if (elem > n) throw out_of_range{"element cannot exceed array length"};
    }

    inline int get_element(const int* const a, const int n, const int i)
    {
        const auto elem = a[i] & clear_history;
        check_element(n, elem);
        return elem;
    }

    // Returns true iff elem is a new duplicate.
    inline bool mark_and_print_if_dupe(const int elem, int& history)
    {
        if (history & seen_twice) return false;

        if (history & seen_once) {
            history |= seen_twice;
            cout << elem << ' ';
            return true;
        }

        history |= seen_once;
        return false;
    }

    // Returns true iff any duplicates were found.
    bool mark_and_print_dupes(int* const a, const int n, int& history_n)
    {
        auto got_dupe = false;

        for (auto i = 0; i != n; ++i) {
            const auto elem = get_element(a, n, i);
            auto& history = (elem == n ? history_n : a[elem]);
            got_dupe |= mark_and_print_if_dupe(elem, history);
        }

        return got_dupe;
    }
}

/*Complete the function below*/
void printDuplicates(int* const a, const int n)
{
    check_n(n);
    int history_n {not_seen}; // a[i] is allowed to be n, track it separately
    if (!mark_and_print_dupes(a, n, history_n)) cout << "-1";
}
