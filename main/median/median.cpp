// median.cpp - calculate the median of command line arguments

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

const char* g_progname;

template <typename T>
T stringToNumber(const std::string& s); // must pass type parameter explicitly

template <typename T>
T sortMedian(std::vector<T>& v); // sort v and return its statistical median

int main(int argc, const char *const *argv);


template <typename T>
T stringToNumber(const std::string& s) // must pass type parameter explicitly
{
    std::stringstream ss (s, std::ios_base::in);
    T x, a;
    if (!(ss >> x) || ss >> a) throw std::runtime_error(
        "s must contain exactly 1 number (except whitespace)");
    return x;
}

template <typename T>            // sort v and return its statistical median
T sortMedian(std::vector<T>& v)
{
    if (v.empty())
        throw std::logic_error("v must be non-empty to have a median");
    
    std::sort(v.begin(), v.end());
    register size_t mid = v.size() / 2;
    return v.size() % 2 == 0 ? (v[mid - 1] + v[mid]) / T(2) : v[mid];
}

int main(int argc, const char *const *argv)
{
    g_progname = argv[0];
    --argc, ++argv;
    std::vector<double> v (argc);

    try {
        for (int i = 0; i != argc; ++i) v[i] = stringToNumber<double>(argv[i]);
        std::cout << sortMedian(v) << std::endl;
        return EXIT_SUCCESS;
    }
    catch (std::runtime_error e) {
        std::cerr << g_progname << ": error: non-numeric input\n";
    }
    catch (std::logic_error e) {
        std::cerr << g_progname << ": error: empty data set has no median\n";
    }

    return EXIT_FAILURE;
}
