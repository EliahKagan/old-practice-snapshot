#include <bits/stdc++.h>
using namespace std;

#define MAX 100
vector<string> printPath(int m[MAX][MAX], int n);
int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	int n;
	cin>>n;
	
	int m[100][100];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>m[i][j];
		}
	}
	
	vector<string> res = printPath(m,n);
	for(int i=0;i<res.size();i++)
	cout<<res[i]<<" ";
	cout<<endl;
}
	return 0;
}

namespace {
    void findPaths(int maze[][MAX], const size_t n, vector<string>& paths)
    {
        const auto fi = n - 1, fj = n - 1;
        string cur;
        
        const function<void(char, size_t, size_t)>
        dfs {[&, n, fi, fj](const char dir, const size_t i, const size_t j) {
            if (i < n && j < n && maze[i][j]) {
                maze[i][j] = 0;
                cur.push_back(dir);
                
                if (i == fi && j == fj) paths.push_back(cur.substr(1u));
                else {
                    dfs('D', i + 1u, j);
                    dfs('L', i, j - 1u);
                    dfs('R', i, j + 1u);
                    dfs('U', i - 1u, j);
                }
                
                cur.pop_back();
                maze[i][j] = 1;
            }
        }};
        
        dfs('_', 0u, 0u);
    }
}

/*The function returns a sorted array of strings which represents
the directions mouse will take to reach the destination.
You are required to complete the below method. */
vector<string> printPath(int maze[][MAX], const int n)
{
    vector<string> paths;
    findPaths(maze, static_cast<size_t>(n), paths);
    //sort(begin(paths), end(paths));
    return paths;
}
