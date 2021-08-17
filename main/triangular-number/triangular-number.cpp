#include <cmath>
#include <iostream>

int main()
{
    using namespace std;

    auto t = 0;
    for (cin >> t; t > 0; --t) {
        auto n = 0L;
        cin >> n;

        // A positive integer n is triangular if and only if 8n+1 is square.
        const auto discriminant = n * 8L + 1L;
        const auto root = lround(sqrt(static_cast<double>(discriminant)));
        std::cout << (root * root == discriminant ? '1' : '0') << '\n';
    }
}
