// coins.cpp - ask user for how many of each coin, then print values and total

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

unsigned int howMany(const std::string& coinPlural);
inline const char* s(const std::string& str);
int main();

unsigned int howMany(const std::string& coinPlural)
{
    for (unsigned int n; ; ) {
        std::cout << "How many " << coinPlural << " do you have? ";
        std::string line;
        std::getline(std::cin, line);
        std::stringstream linestream (line, std::ios_base::in);
        if (linestream >> n) return n;
    }
}

inline const char* s(unsigned int n)
{
    return n == 1 ? "" : "s";
}

int main()
{
    // ask the user how many of each coin type s/he has
    const unsigned int pennies = howMany("pennies"),
        nickels = howMany("nickels"), dimes = howMany("dimes"),
        quarters = howMany("quarters"), halfDollars = howMany("half dollars"),
        dollars = howMany("dollar coins");

    // make a collection of all the counts
    std::vector<unsigned int> v;
    v.push_back(pennies); v.push_back(nickels); v.push_back(dimes);
        v.push_back(quarters); v.push_back(halfDollars); v.push_back(dollars);

    // find the biggest count
    unsigned int max = 0u;
    for (std::vector<unsigned int>::const_iterator it = v.begin();
                it != v.end(); ++it)
        if (*it > max) max = *it;

    // find the smallest width that will fit that number (and thus all counts)
    std::stringstream ss (std::ios_base::out);
    ss << max;
    int w = static_cast<int>(ss.str().size());

    // print all the counts, and a total in dollars
    const char h[] = "\nYou have ";
    std::cout << h << std::setw(w) << pennies << " penn"
                                   << (pennies == 1 ? "y" : "ies") << '.'
        << h << std::setw(w) << nickels << " nickel" << s(nickels) << '.'
        << h << std::setw(w) << dimes << " dime" << s(dimes) << '.'
        << h << std::setw(w) << quarters << " quarter" << s(quarters) << '.'
        << h << std::setw(w) << halfDollars << " half dollar" << s(halfDollars)
        << '.' << h << std::setw(w) << dollars << " dollar coin" << s(dollars)
        << ".\n\nThe value of all your coins is $"  << std::setprecision(2)
        << std::fixed << (pennies + nickels * 5 + dimes * 10 + quarters * 25
            + halfDollars * 50 + dollars * 100) / 100. << ".\n";
}
