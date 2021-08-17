#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace {
    class CannotGoException : public std::out_of_range {
    public:
        CannotGoException(const char* direction, int pos, int reach);

    private:
        static std::string build_message(const char* direction,
                                         int pos, int reach);
    };

    CannotGoException::CannotGoException(const char* const direction,
                                         const int pos, const int reach)
        : std::out_of_range{build_message(direction, pos, reach)}
    {
    }

    std::string CannotGoException::build_message(
            const char* const direction, const int pos, const int reach)
    {
        std::ostringstream out;

        out << "Can't go " << direction
            << " from " << pos << " by " << reach << '.';

        return out.str();
    }
}

namespace {
    class UnreachedPositionsException : public std::logic_error {
    public:
        // pass the number of unreached positions as the unreached parameter
        explicit UnreachedPositionsException(int unreached);

    private:
        static std::string build_message(int unreached);
    };

    UnreachedPositionsException::UnreachedPositionsException(
            const int unreached) : std::logic_error{build_message(unreached)}
    {
    }

    std::string UnreachedPositionsException::build_message(int unreached)
    {
        std::ostringstream out;
        out << unreached << " positions were not reached.";
        return out.str();
    }
}

namespace {
    constexpr auto debug_bfs = false;

    // Subtracts reach from pos, but throws if an overflow would occur.
    inline int go_left(const int pos, const int reach)
    {
        if (pos < std::numeric_limits<int>::min() + reach)
            throw CannotGoException{"left", pos, reach};

        return pos - reach;
    }

    // Adds reach to pos, but throws if an overflow would occur.
    inline int go_right(const int pos, const int reach)
    {
        if (pos > std::numeric_limits<int>::max() - reach)
            throw CannotGoException{"right", pos, reach};

        return pos + reach;
    }

    inline void enqueue_reach(std::unordered_set<int>& next,
                              const int pos, const int reach) // TODO: use abs
    {
        next.insert(go_left(pos, reach));
        next.insert(go_right(pos, reach));
    }

    std::unordered_map<int, int>
    get_steps_to_all_destinations(const int max_dest)
    {
        auto unreached = max_dest + 1;
        std::unordered_map<int, int> dists;
        std::unordered_set<int> cur {0}, next;

        for (auto cur_dist = 0; !cur.empty(); ++cur_dist) {
            if (debug_bfs) std::cerr << cur_dist << " steps:";
            const auto next_dist = cur_dist + 1;

            for (const auto pos : cur) {
                if (dists.find(pos) == dists.end()) { // not previously reached
                    if (debug_bfs) std::cerr << ' ' << pos;
                    dists.emplace(pos, cur_dist);

                    if (0 <= pos && pos <= max_dest && --unreached == 0)
                        return dists;
                }

                enqueue_reach(next, pos, next_dist);
            }

            if (debug_bfs) std::cerr << '\n';
            cur.clear(); // TODO: check if p=cur.erase(p) in loop is faster
            std::swap(cur, next);
        }
        
        throw UnreachedPositionsException{unreached};
    }
}

int main()
{
    constexpr auto max_dest = 1000;
    const auto dists = get_steps_to_all_destinations(max_dest);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto d = 0;
        std::cin >> d;
        std::cout << dists.at(d) << '\n';
    }
}
