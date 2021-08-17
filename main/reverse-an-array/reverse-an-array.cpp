#include <iostream>
#include <stack>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;

        std::stack<int> s;

        for (auto i = n; i > 0; --i) {
            auto k = 0;
            std::cin >> k;
            s.push(k);
        }

        for (auto sep = ""; n > 0; --n) {
            std::cout << sep << s.top();
            sep = " ";
            s.pop();
        }

        std::cout << '\n';
    }
}
