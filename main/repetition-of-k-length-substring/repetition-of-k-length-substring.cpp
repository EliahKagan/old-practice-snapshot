#include<bits/stdc++.h>
using namespace std;
 
// Returns true if str can be coverted to a string
// with k repeated substrings after replacing k
// characters.
bool checkString(string str, int k);

// Driver code
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		
		string s;
		cin>>s;
		int k;
		cin>>k;
      cout<<checkString(s, k)<<endl;
	}
    return 0;
}

/*You are required to complete below method */
bool checkString(string str, int k)
{
    if (str.size() % k != 0u) return false;
    
    unordered_map<string, int> freq;
    for (auto i = 0; i != str.size(); i += k) ++freq[str.substr(i, k)];
    
    if (freq.size() != 2) return freq.size() < 2;
    
    auto p = freq.cbegin();
    return p->second == 1 || (++p)->second == 1;
}
