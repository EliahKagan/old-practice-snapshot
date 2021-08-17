#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace {
    template<typename T>
    struct BasicMatrix {
        vector<vector<T>> a;
    };

    template<typename T>
    vector<T>& operator+=(vector<T>& x, const vector<T>& y)
    {
        auto p = x.begin();
        auto q = y.cbegin();
        for (; p != x.end() && q != y.cend(); ++p, ++q)
            *p += *q;

        return x;
    }

    template<typename T>
    BasicMatrix<T>& operator+=(BasicMatrix<T>& x, const BasicMatrix<T>& y)
    {
        x.a += y.a;
        return x;
    }

    template<typename T>
    BasicMatrix<T> operator+(BasicMatrix<T> x, const BasicMatrix<T>& y)
    {
        return x += y;
    }

    using Matrix = BasicMatrix<int>;
}

int main () {
   int cases,k;
   cin >> cases;
   for(k=0;k<cases;k++) {
      Matrix x;
      Matrix y;
      Matrix result;
      int n,m,i,j;
      cin >> n >> m;
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         x.a.push_back(b);
      }
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         y.a.push_back(b);
      }
      result = x+y;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }
   }
   return 0;
}
