#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <vector>

#ifdef __GNUC__
#define UNUSED gnu::unused
#else
#define UNUSED
#endif

namespace {
    int gcd(int m, int n) noexcept
    {
        while (n != 0) {
            const auto tmp = n;
            n = m % n;
            m = tmp;
        }

        return m;
    }

    struct Point {
        int x, y;
    };

    constexpr bool operator==(const Point& lhs, const Point& rhs) noexcept
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    [[UNUSED]]
    constexpr bool operator!=(const Point& lhs, const Point& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    constexpr bool operator<(const Point& lhs, const Point& rhs) noexcept
    {
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    }

    constexpr bool operator<=(const Point& lhs, const Point& rhs) noexcept
    {
        return lhs < rhs || lhs == rhs;
    }

    [[UNUSED]]
    constexpr bool operator>(const Point& lhs, const Point& rhs) noexcept
    {
        return !(lhs <= rhs);
    }

    [[UNUSED]]
    constexpr bool operator>=(const Point& lhs, const Point& rhs) noexcept
    {
        return !(lhs < rhs);
    }

    inline std::ostream& operator<<(std::ostream& out, const Point& point)
    {
        return out << point.x << ' ' << point.y;
    }

    inline std::istream& operator>>(std::istream& in, Point& point)
    {
        return in >> point.x >> point.y;
    }

    class Line {
        friend constexpr bool operator==(const Line&, const Line&) noexcept;

    public:
        Line(const Point& p, const Point &q) noexcept;

    private:
        int dx_, dy_;
    };

    inline Line::Line(const Point& p, const Point& q) noexcept
            : dx_{q.x - p.x}, dy_{q.y - p.y}
    {
        const auto scale = gcd(dx_, dy_);
        dx_ /= scale;
        dy_ /= scale;
    }

    constexpr bool operator==(const Line& lhs, const Line& rhs) noexcept
    {
        return lhs.dx_ == rhs.dx_ && lhs.dy_ == rhs.dy_;
    }

    [[UNUSED]]
    constexpr bool operator!=(const Line& lhs, const Line& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    using It = std::vector<Point>::const_iterator;

    // Tells if there is a line that contains every given point.
    bool all_collinear(const std::vector<Point>& points)
    {
        const auto last = points.cend();
        auto first = points.cbegin();
        if (first == last) return true; // no points

        const auto& origin = *first;
        while (++first != last && *first == origin) { }
        if (first == last) return true; // no two distinct points

        const Line line {origin, *first};
        return std::all_of(++first, last, [&](const Point& point) noexcept {
            return origin == point || line == Line{origin, point};
        });
    }

#ifdef __clang__
    #pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
    const auto k_tau = std::acos(-1.0) * 2.0;
#ifdef __clang__
#pragma clang diagnostic pop
#endif

    // The angle between (999, 1000) and (1000, 1000) is ~0.0005 radians, so
    // this is small enough to distinguish any distinct angles that may arise.
    constexpr auto k_epsilon = 0.00001;

    // Computes the angle of the arrow from tail to head, clockwise from north.
    // A negative angle may be returned, to be interpreted as counterclockwise.
    inline double azimuth(const Point& tail, const Point& head) noexcept
    {
        return std::atan2(head.x - tail.x, head.y - tail.y);
    }

    // Gets the nonnegative angle from from_angle to to_angle.
    // Rounds down to zero if the angle is smaller than the error margin.
    inline double angle_between(const double from_angle,
                                const double to_angle) noexcept
    {
        const auto delta = to_angle - from_angle;
        if (std::fabs(delta) <= k_epsilon) return 0.0;
        if (delta < 0.0) return delta + k_tau;
        return delta;
    }

    // Computes the taxicab (Manhattan) metric distance between two points.
    // When candidates for the next clockwise point in a convex hull are
    // collinear in the same direction, the farthest of them must be selected.
    // Because they are all in a line, comparisons in the simpler taxicab metric
    // produce the same ordering as those in the Euclidean (Pythagorean) metric.
    inline int taxicab(const Point& a, const Point& b) noexcept
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

    // Finds the next clockwise point in the convex hull, where origin is the
    // current point and ang is the angle that was traveled in to get there.
    // The hull is taken to exclude sequences of more than two collinear points.
    std::tuple<It, double>
    find_next(const std::vector<Point>& points,
              const Point& origin, const double angle) noexcept
    {
        const auto last = points.cend();

        auto best = last;
        auto best_theta = std::numeric_limits<double>::quiet_NaN();
        auto best_delta = std::numeric_limits<double>::infinity();

        for (auto guess = points.cbegin(); guess != last; ++guess) {
            if (*guess == origin) continue;

            const auto theta = azimuth(origin, *guess);
            const auto delta = angle_between(angle, theta);

            if (std::abs(delta - best_delta) <= k_epsilon
                    ? taxicab(origin, *guess) > taxicab(origin, *best)
                    : delta < best_delta) {
                best = guess;
                best_theta = theta;
                best_delta = delta;
            }
        }

        assert(best != last);
        return std::make_tuple(best, best_theta);
    }

    // Computes the convex hull of the given points via Jarvis march.
    // Gives them in clockwise order. Starts with the lowest of leftmost points.
    // The hull is taken to exclude sequences of more than two collinear points.
    std::vector<Point> convex_hull(const std::vector<Point>& points)
    {
        const auto start = std::min_element(points.cbegin(), points.cend());
        assert(start != points.cend());

        std::vector<Point> hull;
        hull.push_back(*start);
        if (points.size() == 1u) return hull;

        It pos {};
        double angle {};
        tie(pos, angle) = find_next(points, *start, 0.0);

        do {
            hull.push_back(*pos);
            tie(pos, angle) = find_next(points, *pos, angle);
        }
        while (pos != start);

        return hull;
    }

    std::vector<Point> read_points()
    {
        std::vector<Point>::size_type count {};
        std::cin >> count;
        if (!count) throw std::domain_error{"need at least one point"};

        std::vector<Point> points (count);
        for (auto& point : points) std::cin >> point;
        return points;
    }

    void display(const std::vector<Point>& points)
    {
        const auto last = points.cend();
        auto first = points.cbegin();
        assert(first != last);

        std::cout << *first;
        while (++first != last) std::cout << ", " << *first;
        std::cout << '\n';
    }

    void configure_io()
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cin.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    }
}

int main()
{
    configure_io();

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto points = read_points();

        if (all_collinear(points)) std::cout << "-1\n";
        else display(convex_hull(points));
    }
}
