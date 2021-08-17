#include "find-the-number-of-islands-g4g-2.h" //#include <bits/stdc++.h>
using namespace std;
#define MAX 1000  

int findIslands(int A[MAX][MAX], int N, int M);
int main() {
    // your code goes here
    int T;
    cin >> T;

    int A[MAX][MAX];
    while (T--)
    {
        int N, M;
        cin >> N >> M;
        memset(A, 0, sizeof A);
        for (int i = 0; i<N; i++)
            for (int j = 0; j<M; j++)
                cin >> A[i][j];
        cout << findIslands(A, N, M) << endl;
    }
    return 0;
}

namespace {
    void fillRegion(int grid[][MAX], const int n, const int m,
                                     const int i, const int j)
    {
        if (0 <= i && i < n && 0 <= j && j < m && grid[i][j]) {
            grid[i][j] = false;
            
            fillRegion(grid, n, m, i - 1, j - 1);
            fillRegion(grid, n, m, i - 1, j);
            fillRegion(grid, n, m, i - 1, j + 1);
            
            fillRegion(grid, n, m, i, j - 1);
            fillRegion(grid, n, m, i, j + 1);
            
            fillRegion(grid, n, m, i + 1, j - 1);
            fillRegion(grid, n, m, i + 1, j);
            fillRegion(grid, n, m, i + 1, j + 1);
        }
    }
}

/*you are required to complete this method*/
int findIslands(int grid[][MAX], const int n, const int m)
{
    auto count = 0;

    for (auto i = 0; i != n; ++i) {
        for (auto j = 0; j != m; ++j) {
            if (grid[i][j]) {
                fillRegion(grid, n, m, i, j);
                ++count;
            }
        }
    }

    return count;
}
