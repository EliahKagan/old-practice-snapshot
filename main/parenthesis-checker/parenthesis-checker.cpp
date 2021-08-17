#include <iostream>
#include <stack>
#include <string>

namespace {
    bool is_balanced(const std::string& str)
    {
        constexpr auto start_mark = '\0'; // any but ')', ']', '}' works here

        std::stack<char> closers;
        closers.push(start_mark);

        for (const auto c : str) {
            switch (c) {
            case '(':
                closers.push(')');
                continue;

            case '[':
                closers.push(']');
                continue;

            case '{':
                closers.push('}');
                continue;

            case ')':
            case ']':
            case '}':
                if (closers.top() != c) return false;
                closers.pop();
                continue;

            default:
                continue; // ignore non-grouping characters
            }
        }

        return closers.top() == start_mark; // only balanced if all are closed
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t >> std::ws; t > 0; --t) {
        std::string s;
        std::getline(std::cin, s);
        std::cout << (is_balanced(s) ? "balanced" : "not balanced") << '\n';
    }
}
