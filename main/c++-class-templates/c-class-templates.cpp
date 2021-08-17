#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

namespace {
    template <typename T>
    class AddElements final {
    public:
        explicit AddElements(const T elem1) : elem1_{elem1} { }
        T add(const T elem2) { return elem1_ + elem2; }

    private:
        const T elem1_;
    };

    template <>
    class AddElements<string> final {
    public:
        explicit AddElements(const string& elem1) : elem1_{elem1} { }
        string concatenate(const string& elem2) { return elem1_ + elem2; }

    private:
        const string elem1_;
    };
}

// code from HackerRank (not to be modified while completing this exercise)
int main () {
  int n,i;
  cin >> n;
  for(i=0;i<n;i++) {
    string type;
    cin >> type;
    if(type=="float") {
        double element1,element2;
        cin >> element1 >> element2;
        AddElements<double> myfloat (element1);
        cout << myfloat.add(element2) << endl;
    }
    else if(type == "int") {
        int element1, element2;
        cin >> element1 >> element2;
        AddElements<int> myint (element1);
        cout << myint.add(element2) << endl;
    }
    else if(type == "string") {
        string element1, element2;
        cin >> element1 >> element2;
        AddElements<string> mystring (element1);
        cout << mystring.concatenate(element2) << endl;
    }
  }
  return 0;
}
