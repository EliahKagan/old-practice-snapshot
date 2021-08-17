#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {
    // Tasks from http://stackoverflow.com/a/117891:

    // 1. Reverse a string
    inline std::string reverse_string(const std::string& s)
    {
        return std::string{std::crbegin(s), std::crend(s)};
    }

    // 1a. Reverse a string (manually)
    std::string manual_reverse_string(std::string s)
    {
        const auto back_pos = s.size() - 1u, istop = s.size() / 2u;

        for (std::string::size_type i{0u}; i != istop; ++i)
            std::swap(s[i], s[back_pos - i]);

        return s;
    }

    // 2. Reverse a sentence
    std::string reverse_sentence(const std::string& s)
    {
        std::istringstream in {s};
        std::vector<std::string> words;
        for (std::string w; in >> w; ) words.push_back(std::move(w));
        
        auto p = std::crbegin(words);
        const auto q = std::crend(words);

        if (p == q) return std::string{};

        std::ostringstream out;
        for (out << *p; ++p != q; ) out << ' ' << *p;
        return out.str();
    }

    // 3. Find the minimum value in a "list"
    template<typename T>
    inline T min_of(const std::vector<T>& a)
    {
        if (a.empty())
            throw std::invalid_argument{"empty container has no minimum"};

        return *std::min_element(std::cbegin(a), std::cend(a));
    }

    // 3a. Find the minimum value in a "list" (manually)
    template<typename T>
    T manual_min_of(const std::vector<T>& a)
    {
        auto p = std::cbegin(a);
        const auto q = std::cend(a);
        
        if (p == q)
            throw std::invalid_argument{"empty container has no minimum"};

        T minval = *p;
        while (++p != q)
            if (minval > *p) minval = *p;

        return minval;
    }

    // 4. Find the maximum valie in a "list"
    template<typename T>
    inline T max_of(const std::vector<T>& a)
    {
        if (a.empty())
            throw std::invalid_argument{"empty container has no maximum"};

        return *std::max_element(std::cbegin(a), std::cend(a));
    }

    // 4a. Find the maximum value in a "list" (manually)
    template<typename T>
    T manual_max_of(const std::vector<T>& a)
    {
        auto p = std::cbegin(a);
        const auto q = std::cend(a);

        if (p == q)
            throw std::invalid_argument{"empty container has no maximum"};

        T maxval = *p;
        while (++p != q)
            if (maxval < *p) maxval = *p;

        return maxval;
    }

    // 5. Calculate a remainder
    template<typename T>
    constexpr T compute_remainder(const T numerator, const T denominator)
    {
        return numerator % denominator;
    }

    template<>
    float compute_remainder<float>(const float numerator,
                                   const float denominator)
    {
        return std::fmod(numerator, denominator);
    }

    template<>
    double compute_remainder<double>(const double numerator,
                                     const double denominator)
    {
        return std::fmod(numerator, denominator);
    }

    template<>
    long double compute_remainder<long double>(const long double numerator,
                                               const long double denominator)
    {
        return std::fmod(numerator, denominator);
    }

    // 6. Return distinct values from a "list" that may have duplicates
    template<typename T>
    std::vector<T> distinct(const std::vector<T>& a)
    {
        std::unordered_set<T> s;
        std::vector<T> b;

        for (const auto& x : a) {
            if (s.find(x) != s.end()) continue;
            s.insert(x);
            b.push_back(x);
        }

        return b;
    }

    template<typename T>
    std::string parse_distinct(const std::string& s)
    {
        std::istringstream in {s};
        std::vector<T> a;
        for (T x {}; in >> x; ) a.push_back(std::move(x));

        const auto b = distinct(a);
        auto p = std::cbegin(b);
        const auto q = std::cend(b);

        if (p == q) return std::string{};

        std::ostringstream out;
        for (out << *p; ++p != q; ) out << ' ' << *p;
        return out.str();
    }

    // 7. Return distinct values and their counts [in order of first apperance]
    template<typename T>
    std::vector<std::pair<T, typename std::vector<T>::size_type>>
    distinct_with_counts(const std::vector<T>& a)
    {
        std::vector<std::pair<T, typename std::vector<T>::size_type>> b;
        std::unordered_map<T, typename decltype(b)::size_type> m;

        for (const auto& x : a) {
            const auto p = m.find(x);

            if (p == m.end()) {
                m.emplace(x, b.size());
                b.emplace_back(x, 1u);
            }
            else ++b[p->second].second;
        }

        return b;
    }

    template<typename T>
    std::string parse_distinct_with_counts(const std::string& s)
    {
        std::istringstream in {s};
        std::vector<T> a;
        for (T x{}; in >> x; ) a.push_back(std::move(x));

        std::ostringstream out;

        auto sep = "";
        for (const auto& y : distinct_with_counts(a)) {
            out << sep << y.first << '(' << y.second << ')';
            sep = " ";
        }

        return out.str();
    }

    // 8. Evaluate sum/difference of terms each consisting of a single
    //    variable, plugging in values for each variable.
    constexpr bool prohibit_empty_sum {false};

    // helper function for failing due to syntax (parsing) errors
    [[noreturn]] inline void parse_error(const std::string& source)
    {
        std::ostringstream out;
        out << "syntax error parsing " << source;
        throw std::invalid_argument{out.str()};
    }

    template<typename T>    // helper function
    T substitute(const char var, const std::unordered_map<char, T>& subs_map)
    {
        try {
            return subs_map.at(var);
        }
        catch (const std::out_of_range&) {
            throw std::invalid_argument{"unsubstituted variable in formula"};
        }
    }

    template<typename T>
    T substitute_and_evaluate(const std::string& expr,
                              const std::unordered_map<char, T>& subs_map)
    {
        std::istringstream in {expr};
        T acc {};
        
        char term {};
        if (in >> term) {
            acc = substitute(term, subs_map);

            for (char op {}; in >> op; ) {
                const auto minus = op == '-';

                if (!(minus || op == '+')) parse_error("formula");
                if (!(in >> term)) parse_error("formula");
                
                if (minus)  acc -= substitute(term, subs_map);
                else        acc += substitute(term, subs_map);
            }
        }
        else if (prohibit_empty_sum) parse_error("formula");

        if (in.eof() || (in >> std::ws).eof()) return acc;
        parse_error("formula");
    }

    template<typename T>    // helper function
    bool parse_one_sub(std::unordered_map<char, T>& subs_map, std::istream& in)
    {
        char var {};
        if (!(in >> var)) return false; // nothing to parse

        char eq {};
        if (!(in >> eq && eq == '=')) parse_error("substitution list");

        T val {};
        if (!(in >> val)) parse_error("substitution list");

        const auto p = subs_map.find(var);

        if (p == subs_map.end()) subs_map.emplace(var, val);
        else if (p->second != val) {
            throw std::invalid_argument(
                    "variable redefinition in substitution list");
        }

        return true; // parsed a var/val pair and added it if it was new
    }

    inline bool read_sep(std::istream& in)
    {
        char sep {}; // accepts ',' or (for internationalization) ';'
        return in >> sep && (sep == ',' || sep == ';');
    }

    template<typename T>    // helper function
    std::unordered_map<char, T> build_subs_map(const std::string& subs_str)
    {
        std::istringstream in {subs_str};
        std::unordered_map<char, T> subs_map;

        if (parse_one_sub(subs_map, in)) {
            while (!(in.eof() || (in >> std::ws).eof())) {
                if (!(read_sep(in) && parse_one_sub(subs_map, in)))
                    parse_error("substitution list");
            }
        }

        return subs_map;
    }

    template<typename T>
    inline T substitute_and_evaluate(const std::string& expr,
                                     const std::string& subs_str)
    {
        return substitute_and_evaluate(expr, build_subs_map<T>(subs_str));
    }

    template<typename T>
    void substitute_and_evaluate_test(const std::string& expr,
                                      const std::string& subs_str)
    {
        try {
            const auto result = substitute_and_evaluate<T>(expr, subs_str);
            std::cout << expr << " | " << subs_str << " = " << result << '\n';
        }
        catch (const std::invalid_argument& e) {
            std::cout << '[' << expr << " | " << subs_str << ":  "
                      << e.what() << "]\n";
        }
    }
}

int main()
{
    std::cout << "String reversal:\n";
    std::cout << '(' << reverse_string("bob likes dogs") << ")\n";
    std::cout << '(' << manual_reverse_string("bob likes dogs") << ")\n";
    std::cout << '(' << reverse_string("Madam, I'm Adam.") << ")\n";
    std::cout << '(' << manual_reverse_string("Madam, I'm Adam.") << ")\n";
    std::cout << '(' << reverse_string("") << ")\n"; // no characters
    std::cout << '(' << manual_reverse_string("") << ")\n";
    std::cout << '(' << reverse_string("foo bar baz") << ")\n"; // odd length
    std::cout << '(' << manual_reverse_string("foo bar baz") << ")\n";

    std::cout << "\nSentence reversal:\n";
    std::cout << '(' << reverse_sentence("bob likes dogs") << ")\n";
    std::cout << '(' << reverse_sentence(" bob  likes\t\n dogs  \t ") << ")\n";
    std::cout << '(' << reverse_sentence("Madam, I'm Adam.") << ")\n";
    std::cout << '(' << reverse_sentence("    Madam,  I'm Adam. ") << ")\n";
    std::cout << '(' << reverse_sentence("") << ")\n"; // no words
    std::cout << '(' << reverse_sentence("  \t \n") << ")\n";
    std::cout << '(' << reverse_sentence("do re mi fa") << ")\n"; // even length

    // create vectors for testing min and max
    std::istringstream in1 {"1 3 5 3 7 3 1 1 5"}, in2 {"foo bar baz quux"};
    std::vector<int> a1;
    for (int n {}; in1 >> n; ) a1.push_back(n);
    std::vector<std::string> a2;
    for (std::string s; in2 >> s; ) a2.push_back(s);

    // display a table of min and max results
    std::cout << '\n' << std::left;
    const auto row = []() -> std::ostream& { return std::cout << std::setw(5); };
    row() << "MIN" << "MAX\n";
    row() << min_of(a1) << max_of(a1) << '\n';
    row() << min_of(a2) << max_of(a2) << '\n';
    row() << manual_min_of(a1) << manual_max_of(a1) << '\n';
    row() << manual_min_of(a2) << manual_max_of(a2) << "\n";

    std::cout << "\nThe \"remainder\" of diving -7 by 4: "
              << compute_remainder(-7, 4) << ' '
              << compute_remainder(-7LL, 4LL) << ' '
              << compute_remainder(-7.f, 4.f) << ' '
              << compute_remainder(-7., 4.) << '\n';

    std::cout << "\nDistinct values in order of appearance:\n";
    std::cout << parse_distinct<int>("1 3 5 3 7 3 1 1 5") << '\n';
    std::cout << parse_distinct<int>("5 1 1 3 7 3 5 3 1") << '\n';
    std::cout << parse_distinct<std::string>("a ba ab a a ba") << '\n';
    std::cout << parse_distinct<std::string>("ba a a ab ba a") << '\n';

    std::cout << "\nDistinct values in order of appearance, with counts:\n";
    std::cout << parse_distinct_with_counts<int>("1 3 5 3 7 3 1 1 5") << '\n';
    std::cout << parse_distinct_with_counts<int>("5 1 1 3 7 3 5 3 1") << '\n';
    std::cout << parse_distinct_with_counts<std::string>("a ba ab a a ba") << '\n';
    std::cout << parse_distinct_with_counts<std::string>("ba a a ab ba a") << '\n';

    std::cout << "\nSimple substitution and evaluation:\n";
    substitute_and_evaluate_test<int>("a + b+c -d", "a=1, b=7, c=3, d=14");
    substitute_and_evaluate_test<int>("a + b+c -d", "a=1, b=7, c=3, d= ");
    substitute_and_evaluate_test<int>("a + b+c -d", "a=1, b=7, c=3, d");
    substitute_and_evaluate_test<int>("a + b+c -d", "a=1, b=7, c=3, ");
    substitute_and_evaluate_test<int>("a + b+c -d", "a=1, b=7, c=3");
    substitute_and_evaluate_test<int>(" x+y-z+x-z ", " x = 1, y = 2, z = 3  ");
    substitute_and_evaluate_test<int>("x + y - z + x - z", "x=1;y=2;z=3;y=2");
    substitute_and_evaluate_test<int>("x + y - z + x - z", "x=1;y=2;z=3;y=4");
    substitute_and_evaluate_test<int>("", "");
    substitute_and_evaluate_test<double>("a + b+c -d", "a=.1,b=.7,c=.3,d=1.4");
    substitute_and_evaluate_test<double>("a + b+c -d", "a=.1,b=.7,c=.3,d=foo");
    substitute_and_evaluate_test<double>("p * q", "p=1.5, q=3.2");
    substitute_and_evaluate_test<double>("p + q", "p=1.5, q=3.2, r=1e20");
}
