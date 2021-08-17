#include <iostream>
#include <queue>

namespace {
    class Flower {
    public:
        explicit Flower(const int cost) : m_cost{cost}, m_incr{cost} { }
        
        Flower(const Flower&) = default;
        Flower(Flower&&) = default;
        Flower& operator=(const Flower&) = delete;
        Flower& operator=(Flower&&) = delete;
        ~Flower() = default;

        int cost() const { return m_cost; }
        Flower& operator++() { m_cost += m_incr; return *this; }

    private:
        int m_cost;
        const int m_incr;
    };

    inline bool operator<(const Flower& lhs, const Flower& rhs)
    {
        return lhs.cost() < rhs.cost();
    }

    inline bool operator>(const Flower& lhs, const Flower& rhs)
    {
        return lhs.cost() > rhs.cost();
    }

    std::priority_queue<Flower> read_flowers(int n)
    {
        std::priority_queue<Flower> flowers;

        while (n-- > 0) {
            auto cost = 0;
            std::cin >> cost;
            flowers.emplace(cost);
        }

        return flowers;
    }
}