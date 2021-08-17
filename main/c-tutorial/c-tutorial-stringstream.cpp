#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

namespace {
    vector<int> parseInts(const string& str) {
        vector<int> v;
        istringstream in {str};
    
        char c;
        do {
            int n;
            if (!(in >> n)) break;
            v.push_back(n);
        }
        while (in >> c && c == ',');

        return v;
    }
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}
