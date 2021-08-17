#include <iostream>
#include <set>
#include <stack>
#include <stdexcept>

inline void push(std::stack<int>& s, std::multiset<int>& m)
{
    auto x = 0;
    std::cin >> x;

    s.push(x);
    m.insert(x);
}

inline void pop(std::stack<int>& s, std::multiset<int>& m)
{
    const auto x = s.top();
    s.pop();
    
    const auto p = m.find(x);
    auto q = p;
    m.erase(p, ++q); // remove just one x
}

inline void print_max(std::multiset<int>& m)
{
    if (m.empty()) throw std::invalid_argument("empty multiset has no max");
    std::cout << *m.crbegin() << '\n';
}

int main()
{
    std::stack<int> s;
    std::multiset<int> m;

    auto n = 0;
    for (std::cin >> n; n > 0; --n) {
        auto q = 0;
        std::cin >> q;

        switch (q) {
            case 1:     push(s, m);     continue;
            case 2:     pop(s, m);      continue;
            case 3:     print_max(m);   continue;
            default:    throw std::out_of_range("invalid query type");
        }
    }
}
