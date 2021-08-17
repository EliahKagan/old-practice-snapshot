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

namespace { // This version outputs values in increasing order.
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
    
    // Returns true iff any duplicates were found.
    bool write_histories(int* const a, const int n, int& history_n)
    {
        auto got_dupe = false;
        
        for (auto i = 0; i != n; ++i) {
            const auto elem = a[i] & clear_history;
            check_element(n, elem);
            
            auto& history = (elem == n ? history_n : a[elem]);
            
            if (history & seen_once) {
                history |= seen_twice;
                got_dupe = true;
            }
            else history |= seen_once;
        }
        
        return got_dupe;
    }
    
    inline void print_if_dupe(const int history, const int value)
    {
        if (history & seen_twice) cout << value << ' ';
    }
    
    void print_dupes(const int* const a, const int n, const int history_n)
    {
        for (auto i = 0; i != n; ++i) print_if_dupe(a[i], i);
        print_if_dupe(history_n, n);
    }
}

/*Complete the function below*/
void printDuplicates(int* const a, const int n)
{
    check_n(n);
    
    int history_n {not_seen}; // a[i] is allowed to be n, track it separately
    
    if (write_histories(a, n, history_n)) print_dupes(a, n, history_n);
    else cout << "-1";
}
