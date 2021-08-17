// primes.cpp - compute primes via trial division or Sieve of Eratosthenes

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept> // for std::logic_error on unimplemented functionality
#include <string>
#include <vector>

// make sure _Noreturn is defined
#ifdef __GNUC__
#define _Noreturn __attribute__ ((noreturn))
#elif defined(MSC_VER)
#define _Noreturn __declspec(noreturn)
#elif !defined(_Noreturn)
#define _Noreturn
#endif

#ifdef NDEBUG
const bool g_debug = false;
#else
const bool g_debug = true;
#endif

#ifdef _WIN32
const bool g_w32 = true;
const char g_sep = '\\';
#else
const bool g_w32 = false;
const char g_sep = '/';
#endif

const size_t g_firstPrime = 2u;

const char* g_progname;

template <typename T>
static std::vector<T> trialDiv(T n, bool nIsBound);

template <typename T>
static std::vector<T> sieve(T n, bool nIsBound);

static inline std::string& lowerize(std::string& s);
static inline std::string& trimExt(std::string& path, const std::string& ext); 
static std::string basename(const std::string& path, char sep);
static _Noreturn void usage(); // print usage message and exit
static bool usingSieve();
int main(int argc, const char* const* argv);

template <typename T>
static std::vector<T> trialDiv(T n, bool nIsBound)
{           // if nIsBound, find primes <= n; otherwise find the first n primes
    if (g_debug) std::clog << g_progname << ": debug: using trial division\n";

    std::vector<T> primes;
    for (T i = T(g_firstPrime);
                (nIsBound ? i : static_cast<T>(primes.size())) <= n; ++i) {
        typename std::vector<T>::const_iterator it = primes.begin();
        for (; it != primes.end() && i % *it != T(0); ++it) { }
        if (it == primes.end()) primes.push_back(i);
    }

    return primes;
}

template <typename T>
static std::vector<T> sieve(T n, bool nIsBound)
{
    if (g_debug)
        std::clog << g_progname << ": debug: using Sieve of Eratosthenes\n";

    if (nIsBound) {
        size_t max = static_cast<size_t>(n);
        if (max < g_firstPrime) return std::vector<T>();
        std::vector<bool> composite (max + 1u, false);

        for (size_t p = g_firstPrime; ; ) {
            // mark pp, (p+1)p, (p+2)p, ... composite (kp for k<p already done)
            for (size_t kp = p * p; kp <= max; kp += p) composite[kp] = true;

            // p -> smallest number >p that we don't know to be composite
            std::vector<bool>::const_iterator it
                = std::find(composite.begin() + p + 1, composite.end(), false);
            if (it == composite.end()) break;
            p = it - composite.begin();
        }

        // fill and return a new vector of primes (i.e., indexes to false)
        std::vector<T> primes;
        for (size_t i = 2u; i <= max; ++i)
            if (!composite[i]) primes.push_back(static_cast<T>(i));

        return primes;
    }
    else throw std::logic_error(
        "incremental Sieve of Eratosthenes (for -n) not yet supported");
}

static inline std::string& lowerize(std::string& s)
{
    for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
        char& c = *it;
        c = static_cast<char>(std::tolower(c));
    }

    return s;
}

static inline std::string& trimExt(std::string& path, const std::string& ext)
{
    if (path.size() > ext.size()
                && path.substr(path.size() - ext.size()) == ext)
        path.erase(path.size() - ext.size());

    return path;
}

static std::string basename(const std::string& path, char sep)
{
    size_t i = path.rfind(sep);
    return i == std::string::npos ? path : path.substr(++i);
}

static _Noreturn void usage() // print usage message and exit
{
    std::cerr << "Usage:  " << g_progname << " [ -n | -b ] <number>\n";
    std::exit(EXIT_FAILURE);
}

static bool usingSieve() //true = Sieve of Eratosthenes, false = trial division
{
    std::string progname (g_progname);
    if (g_w32) trimExt(lowerize(progname), ".exe");
    return basename(progname, g_sep) == "sieve";
}

int main(int argc, const char* const* argv)
{
    g_progname = argv[0];
    std::cout.exceptions(std::ios_base::badbit);

    try {
        unsigned long n;
        bool nIsBound = true;

        // read the 1st command-line arg, see if it's a flag, if so process it
        if (argc == 1) usage();
        std::string s (argv[1]);
        if (s == "-n" || s  == "-b") {
            if (s == "-n") nIsBound = false;
            if (argc != 3) usage();
            s = argv[2];
        }

        // read n from next (possibly 1st) command-line arg
        std::stringstream ss (s, std::ios_base::in);
        if (!(ss >> n) || ss >> s) usage(); // arg should be exactly one number
        if (s[0] == '-') return EXIT_SUCCESS; // user meant n<0 (primes are >1)

        // find primes
        std::vector<unsigned long> primes = usingSieve() ? sieve(n, nIsBound)
                                                      : trialDiv(n, nIsBound);

        // print primes
        for (std::vector<unsigned long>::const_iterator it = primes.begin();
                    it != primes.end(); ++it)
            std::cout << *it << std::endl;

        return EXIT_SUCCESS;
    }
    catch (std::logic_error& e) {
        std::string what (e.what());
        if (what.rfind("not yet supported") == std::string::npos) throw;
        std::cerr << g_progname << ": error: " << e.what() << '\n';
    }
    catch (std::ios_base::failure&)  {
        std::cerr << g_progname << ": error: "
                  << "failure writing to standard output\n";
    }

    return EXIT_FAILURE;
}
