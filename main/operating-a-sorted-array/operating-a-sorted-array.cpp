#include "operating-a-sorted-array.h" //#include<bits/stdc++.h>
using namespace std;
int search(int arr[], int x,int n);
bool insert(int arr[], int y,int n);
bool deleteEle(int arr[], int z,int n);
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x,y,z,a[1000];
		cin>>n;
		for(int i=0;i<n;i++)
			cin>>a[i];
		cin>>x>>y>>z;
		int q=search(a,x,n);
		if(a[q]==x)
			cout<<"1 ";
		else
			cout<<"0 ";
		bool w=insert(a,y,n);
		if(a[search(a,y,n+1)]==y)
			cout<<"1 ";
		else
			cout<<"0 ";
		w=deleteEle(a,z,n+1);
		if(search(a,z,n)!=z)
			cout<<"1 ";
		else
			cout<<"0 ";
		cout<<endl;
	}
}

/*Complete the function(s) below*/

namespace {
    constexpr auto debug = false;
    constexpr auto search_returns_index = true;
}

int search(int* const a, const int x, const int n)
{
    if (debug) cout << "\nDEBUG: search: x=" << x << ", n=" << n << '\n';
    
    if (search_returns_index) // problem description is ambiguous about this
        return static_cast<int>(lower_bound(a, a + n, x) - a);
    else
        return binary_search(a, a + n, x);
}

bool insert(int* const a, const int y, const int n)
{
    if (debug) cout << "\nDEBUG: insert: y=" << y << ", n=" << n << '\n';
    
    const auto q = a + n, p = upper_bound(a, q, y);
    copy_backward(p, q, next(q));
    *p = y;
    return true;
}

bool deleteEle(int* const a, const int z, const int n)
{
    if (debug) cout << "\nDEBUG: deleteEle: z=" << z << ", n=" << n << '\n';
    
    const auto q = a + n, p = lower_bound(a, q, z);
    if (p == q || *p != z) return false;
    
    copy(next(p), q, p);
    return true;
}
