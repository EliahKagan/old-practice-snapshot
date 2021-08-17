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
	//	cout<<p1<<" "<<p2<<endl;
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

/*The function should return a string denoting the 
order of the words in the Alien Dictionary */
string printOrder(string dict[], int N, int k)
{
    constexpr auto alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    bool table[26][26] {};
    
    const auto istop = N - 1;
    for (auto i = 0; i != istop; ++i) {
        for (auto j = i + 1; j != N; ++j) {
            const auto hstop = min(dict[i].size(), dict[j].size());
            for (string::size_type h {}; h != hstop; ++h) {
                if (dict[i][h] != dict[j][h]) {
                    table[dict[i][h] - 'a'][dict[j][h] - 'a'] = true;
                    break;
                }
            }
        }
    }
    
    string ret (alphabet, k);
    
    sort(begin(ret), end(ret), [&table](const char x, const char y) {
        return table[x - 'a'][y - 'a'];
    });
    
    return ret;
}
