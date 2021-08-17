#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {
    enum class Bearing : int {n, e, s, w}; // should be listed in this order
    constexpr auto bearing_count = 4; //-V112 (non-memsize type is deliberate)

    inline std::ostream& operator<<(std::ostream& out, const Bearing bearing)
    {
        switch (bearing) {
            case Bearing::n:    return out << 'N';
            case Bearing::e:    return out << 'E';
            case Bearing::s:    return out << 'S';
            case Bearing::w:    return out << 'W';
        }
    }

    inline void rotate(Bearing& bearing, const int k)
    {
        const auto n = static_cast<int>(bearing);
        bearing = static_cast<Bearing>((n + k) % bearing_count);
    }

    inline void rotate(Bearing& bearing, const char c)
    {
        switch (c) {
            case 'U':   rotate(bearing, 0);     break;
            case 'D':   rotate(bearing, 2);     break;
            case 'L':   rotate(bearing, 3);     break;
            case 'R':   rotate(bearing, 1);     break;

            default:    throw std::invalid_argument("invalid rotation");
        }
    }

    inline void advance(int& x, int &y, const Bearing bearing, const int d)
    {
        switch (bearing) {
            case Bearing::n:    y += d;     break;
            case Bearing::e:    x += d;     break;
            case Bearing::s:    y -= d;     break;
            case Bearing::w:    x -= d;     break;
        }
    }

    inline long hypotenuse(const int x, const int y)
    {
        return std::lround(std::floor(std::sqrt(x * x + y * y)));
    }

    void travel(int m)
    {
        auto bearing = Bearing::n;
        auto x = 0, y = 0;

        while (m-- > 0) {
            auto c = '\0';
            auto d = 0;
            std::cin >> c >> d;

            rotate(bearing, c);
            advance(x, y, bearing, d);
        }

        std::cout << hypotenuse(x, y) << ' ' << bearing << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto m = 0;
        std::cin >> m;
        travel(m);
    }
}
