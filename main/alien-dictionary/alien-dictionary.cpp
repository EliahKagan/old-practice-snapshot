/* script for test case http://code.geeksforgeeks.org/PetjYq */
#include<bits/stdc++.h>

using namespace std;

string printOrder(string [], int , int );
string order;
bool f(string a,string b)
{
    int p1=0;int p2=0;
    for(int i=0;i<min(a.size(),b.size()) and p1 ==p2;i++ )
    {
        p1 = order.find(a[i]);
        p2 = order.find(b[i]);
    //  cout<<p1<<" "<<p2<<endl;
    }
    
    if(p1 == p2 and a.size()!=b.size())
    return a.size()<b.size();
    
    return p1<p2;
}
    
// Driver program to test above functions
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
    string s[n];
    for(int i=0;i<n;i++)cin>>s[i];
    
        string ss = printOrder(s,n,k);
        order="";
        for(int i=0;i<ss.size();i++)
        order+=ss[i];
        
        string temp[n];
        std::copy(s, s + n, temp);
        sort(temp,temp+n,f);
        
        bool f= true;
        for(int i=0;i<n;i++)
        if(s[i]!=temp[i])f=false;
        
        cout<<f;
        cout<<endl;
        
    }
    return 0;
}

namespace {
    constexpr int kmax = 26;
    
    using Table = array<array<bool, kmax>, kmax>;
    
    constexpr int ind(const char c)
    {
        return c - 'a';
    }
    
    inline void add_word_comparison(Table& adj,
                                    const string& lhs, const string& rhs)
    {
        const auto hstop = min(lhs.size(), rhs.size());
        
        for (string::size_type h {}; h != hstop; ++h) {
            if (lhs[h] != rhs[h]) {
                adj[ind(lhs[h])][ind(rhs[h])] = true;
                break;
            }
        }
    }
    
    void populate_adjacency_table(Table& adj,
                                  const string* const dict, const int n)
    {
        const auto istop = n - 1;
        
        for (auto i = 0; i != istop; ++i) {
            for (auto j = i + 1; j != n; ++j)
                add_word_comparison(adj, dict[i], dict[j]);
        }
    }
    
    // Let val() be the inverse of idx(). The connect() function writes a
    // true in adj for each x for which val(mark) <= val(cur) < x, indicating
    // val(mark) < x. connect() must only be called with mark, cur such that
    // val(mark) <= val(cur). Nonrecursive calls should use mark == cur.
    void connect(Table& adj, const int k, const int mark, const int cur)
    {
        for (auto next = 0; next != k; ++next) {
            if (adj[cur][next]) {
                adj[mark][next] = true;
                connect(adj, k, mark, next);
            }
        }
    }
    
    void make_table_transitive(Table& adj, const int k)
    {
        for (int i = 0; i != k; ++i) connect(adj, k, i, i);
    }
    
    string create_sorted_alphabet(const Table& adj, const int k)
    {
        string ret ("abcdefghijklmnopqrstuvwxyz", k);
        
        sort(begin(ret), end(ret), [&adj](const char x, const char y) {
            return adj[ind(x)][ind(y)];
        });
        
        return ret;
    }
}

/*The function should return a string denoting the 
order of the words in the Alien Dictionary */
string printOrder(string* const dict, const int n, const int k)
{
    Table adj {};
    
    populate_adjacency_table(adj, dict, n);
    make_table_transitive(adj, k);
    
    return create_sorted_alphabet(adj, k);
}
