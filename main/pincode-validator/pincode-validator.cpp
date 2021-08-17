#include <algorithm>
#include <iostream>
#include <regex>
#include <set>
#include <string>

int main()
{
    const std::regex re {R"(\d{3}-\d\d-\d\d-\d{8}-[A-Z])",
            std::regex_constants::ECMAScript | std::regex_constants::optimize};

    std::set<std::string> codes; // automatically lexicographically sorted

    auto n = 0;
    for (std::cin >> n >> std::ws; n > 0; --n) {
        std::string s;
        std::getline(std::cin, s);

        std::for_each(std::sregex_iterator{s.cbegin(), s.cend(), re},
                      std::sregex_iterator{},
                      [&](const std::smatch& m) { codes.insert(m.str()); });
    }

    if (codes.empty())
        std::cout << "JUNK\n";
    else
        for (const auto& code : codes) std::cout << code << '\n';
}
