// sum.cxx - sum numbers given interactively by the user

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <cassert>
#include <numeric> // for std::accumulate

using namespace std;

namespace {
    template<typename T>
    T sum(const vector<T>& seq)
    {
        T n {};
        for (const auto k : seq) n += k;
        return n;
    }

    template<typename T>
    void print_sum(const vector<T>& seq)
    {
        const auto n = sum(seq);
        assert(n == accumulate(begin(seq), end(seq), T{}));
        cout << "The sum is " << n << ".\n";
    }

    template<typename T>
    vector<T> read_values(const string prompt)
    {
        const auto err = []() {
            cerr << "Failed to read a line of space-separated values.\n";
            exit(EXIT_FAILURE);
        };

        cout << prompt << ":  " << flush;

        string line;
        if (!getline(cin, line)) err();
        istringstream in {line};

        vector<T> seq;
        for (T x; in >> x; ) seq.push_back(x);
        if (!(in >> ws).eof()) err();
        return seq;
    }
}

int main(int argc, char **argv)
{
    if (any_of(argv + 1, argv + argc, [](string s) { return s == "-f"; }))
        print_sum(read_values<double>("Enter some numbers"));
    else
        print_sum(read_values<long>("Enter some integers"));
}
