// timeloop.cxx - times a loop (see below for results)
// Based on TC++PL4 X.6[3] (http://stroustrup.com/4thExercises.pdf).

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <new>
#include <random>
#include <regex>
#include <stdexcept>
#include <sstream>
#include <string>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif
#if defined(__GNUC__) || defined(__clang__)
#define ATTR(...) __attribute__((__VA_ARGS__))
#else
#define ATTR(...)
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif

namespace {
#ifdef _WIN32
    constexpr bool windows {true};
#else
    constexpr bool windows {false};
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
    std::string progname;
#ifdef __clang__
#pragma clang diagnostic pop
#endif

    void set_progname(const char* a)
    {
        progname = a;
        const auto last_sep = progname.rfind(windows ? '\\' : '/');
        if (last_sep != std::string::npos) progname.erase(0, last_sep + 1);
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4127 )
#endif
        if (windows) {
#ifdef _MSC_VER
#pragma warning( pop )
#endif
            progname = std::regex_replace(progname,
                                          std::regex{R"(\.exe$)"}, "");
        }
    }

    [[noreturn]] ATTR(format(printf, 1, 2)) void die(const char* fmt, ...)
    {
        std::cerr << progname << ": error: ";

        std::va_list v;
        va_start(v, fmt);
        std::vfprintf(stderr, fmt, v);
        va_end(v);

        std::cerr << '\n';
        std::exit(EXIT_FAILURE);
    }

    template<typename T> T get_reps(std::string s)
    {
        if (std::regex_search(s, std::regex{R"(\s*\+?\d+\s*)"})) {
            std::istringstream ss {s};
            T i;
            if (ss >> i) return i;
        }

        die("can't generate \"%s\" numbers (how many is that?)", s.c_str());
    }

    using Vec = std::vector<std::random_device::result_type>;

    void random_fill(Vec& v, Vec::size_type n)
    {
        try { v.reserve(n); }
        catch (const std::length_error&) {
            die(windows ? "%Iu numbers is too many to store"
                        : "%zu numbers is too many to store",
                static_cast<std::size_t>(n));
        }

        std::cout << "Generating " << n << " numbers... " << std::flush;

        using namespace std::chrono;

        const auto ti = high_resolution_clock::now();
        for (std::random_device r; n != 0ul; --n) v.push_back(r());
        const auto tf = high_resolution_clock::now();

        std::cout << "took "
            << duration_cast<milliseconds>(tf - ti).count() << "ms."
            << std::endl;
    }
}

int main(int argc, char* argv[])
{
    constexpr Vec::size_type default_reps {1'000'000ul};

    set_progname(argv[0]);
    std::cout.exceptions(std::ios_base::badbit | std::ios_base::failbit
                                               | std::ios_base::eofbit);

    try {
        Vec v;
        random_fill(v, argc > 1 ? get_reps<Vec::size_type>(argv[1])
                                : default_reps);

        if (!v.empty()) {
            std::sort(v.begin(), v.end());
            std::cout << "Lowest random number was " << v.front()
                << ", highest was " << v.back() << '.' << std::endl;
        }
    }
    catch(const std::bad_alloc&) {
        die("not enough memory");
    }
    catch(const std::ios_base::failure&) {
        die("failure writing to standard output");
    }
}

/* 
    Results:

    ek@DOMO C:\Users\ek\source
    > cl /nologo /EHsc /W4 timeloop.cxx
    timeloop.cxx

    ek@DOMO C:\Users\ek\source
    > timeloop 100000000
    Generating 100000000 numbers... took 31644ms.
    Lowest random number was 74, highest was 4294967294.

    ek@DOMO C:\Users\ek\source
    > cl /nologo /EHsc /W4 /O2 timeloop.cxx
    timeloop.cxx

    ek@DOMO C:\Users\ek\source
    > timeloop 100000000
    Generating 100000000 numbers... took 18170ms.
    Lowest random number was 97, highest was 4294967154.

    ek@DOMO C:\Users\ek\source
    > cl /nologo /EHsc /W4 timeloop.cxx
    timeloop.cxx

    ek@DOMO C:\Users\ek\source
    > timeloop 100000000
    Generating 100000000 numbers... took 31179ms.
    Lowest random number was 122, highest was 4294967118.

    ek@DOMO C:\Users\ek\source
    > cl /nologo /EHsc /W4 /O2 timeloop.cxx
    timeloop.cxx

    ek@DOMO C:\Users\ek\source
    > timeloop 100000000
    Generating 100000000 numbers... took 17827ms.
    Lowest random number was 44, highest was 4294967282.
*/