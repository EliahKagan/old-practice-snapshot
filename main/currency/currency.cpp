// currency.cpp - perform some currency conversions (8 July 2013 rates)

#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// make sure _Noreturn is defined
#ifdef __GNUC__
#define _Noreturn __attribute__ ((noreturn))
#elif defined(MSC_VER)
#define _Noreturn __declspec(noreturn)
#elif !defined(_Noreturn)
#define _Noreturn
#endif

const float g_eurInUsd = 0.780488f, g_gbpInUsd = 0.672337f,
                                    g_jpyInUsd = 101.252998f;

enum Currency { USD, EUR, GBP, JPY };

const char* g_progname;

std::string& upperize(std::string& s);
_Noreturn void usage(); // print usage message and exit
bool parse(const std::string& line, float& amount, std::string& unit);
_Noreturn void currencyError(Currency cur);
const char* abbrev(Currency cur);
float toUsd(float amount, Currency cur);
float fromUsd(float amount, Currency cur);
inline float conv(float amount, Currency curFrom, Currency curTo);
void doConv(float amount, Currency curFrom, Currency curTo);
void doAllConvs(float amount, Currency cur);
void doAllConvs(float amount, const std::string& unit);
int main(int argc, const char *const *argv);

std::string& upperize(std::string& s)
{
    for (std::string::iterator it = s.begin(); it != s.end(); ++it)
        *it = static_cast<char>(std::toupper(*it));

    return s;
}

_Noreturn void usage() // print usage message and exit
{
    std::cerr << "Usage:  " << g_progname << " [ <amount> <unit> ]\n";
    std::exit(EXIT_FAILURE);
}

bool parse(const std::string& line, float& amount, std::string& unit)
{           // returns false on failure
    std::stringstream linestream (line, std::ios_base::in);
    std::string extraneous;
    return linestream >> amount >> unit && !(linestream >> extraneous);
}

_Noreturn void currencyError(Currency cur)
{
    assert(cur == USD || cur == EUR || cur == GBP || cur == JPY);
    std::cerr << g_progname << ": error: \"impossible\" situation, "
              << "contact developer\n";
    std::exit(EXIT_FAILURE);
}

const char* abbrev(Currency cur) // use letter abbrevs to avoid font issues
{
    if (cur == USD) return "USD";
    if (cur == EUR) return "EUR";
    if (cur == GBP) return "GBP";
    if (cur == JPY) return "JPY";
    currencyError(cur);
}

float toUsd(float amount, Currency cur)
{
    switch (cur) {
        case USD: return amount;
        case EUR: return amount / g_eurInUsd;
        case GBP: return amount / g_gbpInUsd;
        case JPY: return amount / g_jpyInUsd;
        default:  currencyError(cur);
    }
}

float fromUsd(float amount, Currency cur)
{
    switch (cur) {
        case USD: return amount;
        case EUR: return amount * g_eurInUsd;
        case GBP: return amount * g_gbpInUsd;
        case JPY: return amount * g_jpyInUsd;
        default:  currencyError(cur);
    }
}

inline float conv(float amount, Currency curFrom, Currency curTo)
{
    return fromUsd(toUsd(amount, curFrom), curTo);
}

void doConv(float amount, Currency curFrom, Currency curTo)
{
    if (curFrom != curTo) { // don't show a self-conversion
        std::cout << "\t" << std::setprecision(curTo == JPY ? 1 : 2)
                  << std::fixed << conv(amount, curFrom, curTo) << ' '
                  << abbrev(curTo) << '\n';
    }
}

void doAllConvs(float amount, Currency cur)
{
    std::cout << "On 8 July 2013, " << amount << ' ' << abbrev(cur)
              << " was equal to (i.e., would exchange for):\n\n";

    doConv(amount, cur, USD);
    doConv(amount, cur, EUR);
    doConv(amount, cur, GBP);
    doConv(amount, cur, JPY);
}

void doAllConvs(float amount, const std::string& unit)
{
    Currency cur;
    std::string u (unit);
    upperize(u);
    
    if (u == "USD" || u == "$" || u == "DOLLAR" || u == "DOLLARS")
        cur = USD;
    else if (u == "EUR" || u == "€" || u == "EURO" || u == "EUROS")
        cur = EUR;
    else if (u == "GBP" || u == "£" || u == "₤" || u == "pound"
                || u == "pounds")
        cur = GBP;
    else if (u == "JPY" || u == "¥" || u == "YEN") cur = JPY;
    else {
        std::cerr << g_progname << ": error: unrecogized unit: " << unit
                  << '\n';
        std::exit(EXIT_FAILURE);
    }

    doAllConvs(amount, cur);
}

int main(int argc, const char *const *argv)
{
    g_progname = argv[0];

    float amount;
    std::string line, unit;

    for (++argv; argc != 1; --argc, ++argv) (line += *argv) += ' ';
    
    if (!line.empty()) { // use command-line arguments
        if (!parse(line, amount, unit)) usage();
    } else { // no command-line arguments to use
        do {
            std::cout << "Please enter a currency amount followed by a unit: ";
            getline(std::cin, line);
        }
        while (!parse(line, amount, unit));

        std::cout << '\n';
    }

    doAllConvs(amount, unit);
    return EXIT_SUCCESS;
}
