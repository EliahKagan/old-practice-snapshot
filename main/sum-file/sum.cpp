// Reads integers from a text file and computes their sum. Uses intmax_t to
// accommodate fairly large and fairly small sums, but does nothing to avoid
// or detect overflow (even though singed overflow in C++ is UB). Stops at the
// end of the file or when text in the file is encountered that cannot be
// interpreted as an integer.
//
// Usage:  ./sum PATH

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // for std::strerror
#endif

#include <cassert>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string_view>

namespace {
    std::string_view program_name;

    void initialize(const int argc, const char* const* const argv)
    {
        assert(argc > 0);
        program_name = argv[0];

        std::ios_base::sync_with_stdio(false);
    }

    [[noreturn]] void die(const std::string_view message)
    {
        std::cerr << program_name << ": error: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv)
{
    initialize(argc, argv);
    if (argc < 2) die("too few arguments");
    if (argc > 2) die("too many arguments");

    std::ifstream in {argv[1]};
    if (!in) die(std::strerror(errno));

    std::cout << std::accumulate(std::istream_iterator<std::intmax_t>{in},
                                 std::istream_iterator<std::intmax_t>{},
                                 std::intmax_t{})
              << '\n';
}
