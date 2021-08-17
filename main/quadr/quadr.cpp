// quadr.cpp - solve quadratic equations

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

// define isnan() and finite() for MSVC++ and for other compilers (like GCC)
#ifdef _MSC_VER
#include <cfloat>
#ifndef isnan
#define isnan _isnan
#endif
#ifndef isfinite
#define isfinite _finite
#endif
#else // !defined (_MSC_VER)
#ifndef isnan
#define isnan std::isnan
#endif
#ifndef isfinite
#define isfinite std::isfinite
#endif
#endif // !defined (_MSC_VER)

template <typename T>
bool solveQuadratic(T a, T b, T c, T& x1, T& x2);

template <typename T>
void getCoefficient(const std::string& name, T& q);

void run();
int main(int argc, const char* const* argv);

template <typename T>
bool solveQuadratic(T a, T b, T c, T& x1, T& x2) // false means no real roots
{
    if (a == T(0.)) { // linear case
        x1 = -c / b; // not a double root, make x1 the root and x2 NaN
        x2 = std::numeric_limits<T>::quiet_NaN();
        return isfinite(x1);
    }

    T r = std::sqrt(b * b - T(4.) * a * c), d = T(2.) * a;
    if (!isfinite(r)) return false;
    
    x1 = (-b + r) / d;
    x2 = (-b - r) / d;
    return true;
}

template <typename T>
void getCoefficient(const std::string& name, T& q)
{
    for (std::string line, extra; ; ) {
        std::cout << name << " = ";
        std::getline(std::cin, line);
        std::stringstream linestream (line, std::ios_base::in);
        if (linestream >> q && !(linestream >> extra)) break; // just 1 num
    }
}

void run()
{
    std::cout << "a x^2  +  b x  +  c\n\n";
    double a, b, c, x1, x2;
    getCoefficient("a", a); getCoefficient("b", b); getCoefficient("c", c);
    std::cout << '\n';

    if (!solveQuadratic(a, b, c, x1, x2)) std::cout << "No real roots.\n";
    else if (isnan(x2)) std::cout << "Single root: x = " << x1 << "\n";
    else if (x1 == x2) std::cout << "Double root: x = " << x1 << ".\n";
    else std::cout << "Separate roots: x1 = " << x1 << "; x2 = " << x2 << ".\n";
}

int main(int argc, const char* const* argv)
{
    std::cout.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    std::cin.exceptions(std::ios_base::badbit);
    
    try {
        run();
        std::cout << std::flush;
        return EXIT_SUCCESS;
    }
    catch (std::ios_base::failure&) {
        if (std::cout.rdstate() | std::ios_base::failbit) throw;
        else if (std::cout.bad())
            std::cerr << argv[0]
                      << ": error: failure writing to standard output\n";
        else if (std::cin.bad())
            std::cerr << argv[0]
                      << ": error: failure reading from standard input\n";
        else throw;

        return EXIT_FAILURE;
    }
}
