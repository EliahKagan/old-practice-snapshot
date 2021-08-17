/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

class Solution {
public:
    static vector<Point> outerTrees(const vector<Point>& points);
};

namespace {
    using It = vector<Point>::const_iterator;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
    // Structural equality relation on Point objects.
    const auto point_eq = [](const Point& lhs, const Point& rhs) noexcept {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    };

    // Strict less than relation on Point objects, comparing x- then y-coords.
    const auto point_lt = [](const Point& lhs, const Point& rhs) noexcept {
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    };
#ifdef __clang__
#pragma clang diagnostic pop
#endif

    int gcd(int m, int n) noexcept
    {
        while (n != 0) {
            const auto tmp = n;
            n = m % n;
            m = tmp;
        }

        return m;
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

#ifdef __GNUC__
    [[gnu::unused]]
#endif
    constexpr bool operator!=(const Line& lhs, const Line& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    bool all_collinear(It first, const It last) noexcept
    {
        if (first == last) return true; // no points

        const auto& origin = *first;
        while (++first != last && point_eq(origin, *first)) { }
        if (first == last) return true; // no two distinct points

        const Line line {origin, *first};
        return all_of(++first, last, [&](const Point& point) noexcept {
            return point_eq(origin, point) || line == Line{origin, point};
        });
    }

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
    const auto k_tau = acos(-1.0) * 2.0;
#ifdef __clang__
#pragma clang diagnostic pop
#endif

    // The angle between (99, 100) and (100, 100) is ~0.005 radians, so this is
    // sufficiently small to distinguish any distinct angles that will arise.
    constexpr auto k_epsilon = 0.0001;

    // Computes the angle of the arrow from tail to head, clockwise from north.
    // A negative angle may be returned, to be interpreted as counterclockwise.
    inline double azimuth(const Point& tail, const Point& head) noexcept
    {
        return atan2(head.x - tail.x, head.y - tail.y);
    }

    // Gets the nonnegative angle from from_angle to to_angle.
    // Rounds down to zero if the angle is smaller than the error margin.
    inline double angle_between(const double from_angle,
                                const double to_angle) noexcept
    {
        const auto delta = to_angle - from_angle;
        if (fabs(delta) <= k_epsilon) return 0.0;
        if (delta < 0.0) return delta + k_tau;
        return delta;
    }

    // Computes the taxicab (Manhattan) metric distance between two points.
    // When candidates for the next clockwise point in a convex hull are
    // collinear in the same direction, the closest of them must be selected.
    // Because they are all in a line, comparisons in the simpler taxicab metric
    // produce the same ordering as those in the Euclidean (Pythagorean) metric.
    inline int taxicab(const Point& a, const Point& b) noexcept
    {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    // Finds the next clockwise point in the convex hull, where origin is the
    // current point and ang is the angle that was traveled in to get there.
    // Sequences of more than two collinear points are *not* excluded, and if
    // *all* provided points are collinear (and there are more than two) then
    // successive calls will return some of the same points twice.
    tuple<It, double>
    find_next(const vector<Point>& points,
              const Point& origin, const double angle) noexcept
    {
        const auto last = points.cend();

        auto best = last;
        auto best_theta = numeric_limits<double>::quiet_NaN();
        auto best_delta = numeric_limits<double>::infinity();

        for (auto guess = points.cbegin(); guess != last; ++guess) {
            if (point_eq(origin, *guess)) continue;

            const auto theta = azimuth(origin, *guess);
            const auto delta = angle_between(angle, theta);

            if (abs(delta - best_delta) <= k_epsilon
                    ? taxicab(origin, *guess) < taxicab(origin, *best)
                    : delta < best_delta) {
                best = guess;
                best_theta = theta;
                best_delta = delta;
            }
        }

        assert(best != last);
        return make_tuple(best, best_theta);
    }
}

vector<Point> Solution::outerTrees(const vector<Point>& points)
{
    vector<Point> hull;
    const auto first = cbegin(points), last = cend(points);

    if (all_collinear(first, last)) {
        hull.assign(first, last);
        const auto d_first = begin(hull), d_last = end(hull);
        sort(d_first, d_last, point_lt);
        hull.erase(unique(d_first, d_last, point_eq), d_last);
        return hull;
    }

    const auto start = min_element(first, last, point_lt);
    auto pos = start;
    auto angle = 0.0;

    do {
        hull.push_back(*pos);
        tie(pos, angle) = find_next(points, *pos, angle);
    }
    while (!point_eq(*pos, *start));

    return hull;
}
