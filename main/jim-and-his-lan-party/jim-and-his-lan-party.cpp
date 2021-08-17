#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    using std::size_t;

    class DisjointPlayerSets {
    public:
        class iterator {
            friend class DisjointPlayerSets;

            friend bool operator==(const iterator& lhs,
                                   const iterator& rhs) noexcept;

        public:
            using difference_type = void;
            using value_type = int;
            using pointer = void;
            using reference = value_type; // OK, we are not a ForwardIterator
            using iterator_category = std::input_iterator_tag;

            int operator*() const noexcept;
            iterator& operator++() noexcept;
            iterator operator++(int) noexcept;

        private:
            static constexpr auto game_not_started = -1;

            explicit iterator(std::vector<int>::const_iterator pos) noexcept;

            std::vector<int>::const_iterator pos_;
        };

        using const_iterator = iterator;

        // @param player_games  player -> game
        explicit DisjointPlayerSets(const std::vector<unsigned>& player_games,
                                    size_t game_count);

        // advances the clock, joining and merging contributions from player1's
        // and player2's sublans if they were not already joined
        void connect(size_t player1, size_t player2);

        // begin/cbegin and end/cend iterate through game start times
        iterator begin() const noexcept;
        iterator cbegin() const noexcept { return begin(); }
        iterator end() const noexcept;
        iterator cend() const noexcept { return end(); }

    private:
        // (game -> negative population) map type
        using Contributions = std::unordered_map<unsigned, int>;

        // finds the leader of the player's connected sublan
        size_t find_set(size_t player) noexcept;

        // perform a union of the sublans by rank if they were separate
        // @return the old leaders, with the new leader first
        std::pair<size_t, size_t> unite(size_t player1,
                                        size_t player2) noexcept;

        // merges the population contributions of what had been two sublans
        void merge_contribs(size_t dest_player, size_t src_player);

        // merges two (game, population) hash tables, removing and recording
        // start times for games that have reached their starting populations
        void merge_nontrivial_contribs(Contributions& dest,
                                       const Contributions& src);

        // set leader -> (game -> negative population)
        std::vector<std::unique_ptr<Contributions>> contribs_;

        // player -> nonnegatve DSU parent, or negative DSU rank if set leader
        std::vector<int> parents_or_ranks_;

        // game -> negative population target, or nonneg start time if started
        std::vector<int> pop_targets_or_start_times_;

        // current time
        int time_ {0};
    };

    inline bool operator==(const DisjointPlayerSets::iterator& lhs,
                           const DisjointPlayerSets::iterator& rhs) noexcept
    {
        return lhs.pos_ == rhs.pos_;
    }

    inline bool operator!=(const DisjointPlayerSets::iterator& lhs,
                           const DisjointPlayerSets::iterator& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline int DisjointPlayerSets::iterator::operator*() const noexcept
    {
        const auto start_time = *pos_;
        return start_time < 0 ? game_not_started : start_time;
    }

    inline auto DisjointPlayerSets::iterator::operator++() noexcept
            -> iterator&
    {
        ++pos_;
        return *this;
    }

    inline auto DisjointPlayerSets::iterator::operator++(int) noexcept
            -> iterator
    {
        auto ret = *this;
        ++pos_;
        return ret;
    }

    inline DisjointPlayerSets::iterator::iterator(
            const std::vector<int>::const_iterator pos) noexcept
        : pos_{pos}
    {
    }

    DisjointPlayerSets::DisjointPlayerSets(
            const std::vector<unsigned>& player_games, const size_t game_count)
        : contribs_(player_games.size()),
          parents_or_ranks_(player_games.size(), -1),
          pop_targets_or_start_times_(game_count)
    {
        const auto player_count = player_games.size();

        // determine how many players are needed for each game
        for (size_t player {0u}; player != player_count; ++player) {
            const auto game = player_games[player];
            --pop_targets_or_start_times_[static_cast<size_t>(game)];
        }

        // start single-player games immediately
        for (auto& elem : pop_targets_or_start_times_)
            if (elem == -1) elem = 0;

        // record players' population contributions toward multiplayer games
        for (size_t player {0u}; player != player_count; ++player) {
            const auto game = player_games[player];
            if (pop_targets_or_start_times_[static_cast<size_t>(game)] != 0) {
                auto& p = contribs_[player];
                p = std::make_unique<Contributions>();
                p->emplace(game, -1);
            }
        }
    }

    void DisjointPlayerSets::connect(size_t player1, size_t player2)
    {
        // one connection per tick of the clock
        ++time_;

        // actually connect the sublans (if they are separate)
        const auto endpoints = unite(player1, player2);

        // unless the sublans were already joined, merge their contributions
        if (endpoints.first != endpoints.second)
            merge_contribs(endpoints.first, endpoints.second);
    }

    size_t DisjointPlayerSets::find_set(size_t player) noexcept
    {
        // find the leader
        auto leader = player;
        while (parents_or_ranks_[leader] >= 0)
            leader = static_cast<size_t>(parents_or_ranks_[leader]);

        // compress the path
        for (const auto lead = static_cast<int>(leader); player != leader; ) {
            const auto parent = static_cast<size_t>(parents_or_ranks_[player]);
            parents_or_ranks_[player] = lead;
            player = parent;
        }

        return leader;
    }

    std::pair<size_t, size_t> DisjointPlayerSets::unite(size_t player1,
                                                        size_t player2) noexcept
    {
        // find the leaders
        player1 = find_set(player1);
        player2 = find_set(player2);

        // if the leaders are not already the same, then perform union by rank
        if (player1 != player2) {
            if (parents_or_ranks_[player1] > parents_or_ranks_[player2]) {
                // player 2 has superior (more negative) rank; it stays leader
                std::swap(player1, player2);
            }
            else if (parents_or_ranks_[player1] == parents_or_ranks_[player2]) {
                // players have equal rank, so promote player1
                --parents_or_ranks_[player1];
            }

            // whichever player is currently player1 remains the leader
            parents_or_ranks_[player2] = static_cast<int>(player1);
        }

        return {player1, player2};
    }

    void DisjointPlayerSets::merge_contribs(const size_t dest_player,
                                            const size_t src_player)
    {
        auto& srcp = contribs_[src_player];
        if (!srcp) return;

        auto& destp = contribs_[dest_player];
        if (!destp) {
            destp = std::move(srcp);
            return;
        }

        if (destp->size() < srcp->size()) std::swap(destp, srcp);
        merge_nontrivial_contribs(*destp, *srcp);
        srcp = nullptr;
        if (destp->empty()) destp = nullptr;
    }

    void DisjointPlayerSets::merge_nontrivial_contribs(Contributions& dest,
                                                       const Contributions& src)
    {
        const auto qq = std::cend(src);
        for (auto q = std::cbegin(src); q != qq; ++q) {
            const auto game = q->first;
            const auto p = dest.find(game);

            if (p == std::end(dest)) {
                dest.insert(*q);
                continue;
            }

            auto& elem = pop_targets_or_start_times_[static_cast<size_t>(game)];

            if ((p->second += q->second) == elem) {
                elem = time_;
                dest.erase(p);
            }
        }
    }

    inline auto DisjointPlayerSets::begin() const noexcept -> iterator
    {
        return iterator{std::cbegin(pop_targets_or_start_times_)};
    }

    inline auto DisjointPlayerSets::end() const noexcept -> iterator
    {
        return iterator{std::cend(pop_targets_or_start_times_)};
    }

    std::vector<unsigned> read_player_games(const size_t n)
    {
        std::vector<unsigned> player_games (n + 1u); // +1 for 1-based indexing

        const auto pp = std::end(player_games);
        for (auto p = std::next(std::begin(player_games)); p != pp; ++p)
            (void)std::scanf("%u", &*p);

        return player_games;
    }
}

int main()
{
    // read initial parameters
    size_t n, m {};
    unsigned q {};
    (void)std::scanf("%zu%zu%u", &n, &m, &q);

    // read everyone's game and initialize the model (+1 for 1-based indexing)
    DisjointPlayerSets network {read_player_games(n), m + 1u};

    // read connection information and apply all the connections in order
    for (size_t u {}, v {}; q != 0u; --q) {
        (void)std::scanf("%zu%zu", &u, &v);
        network.connect(u, v);
    }

    // output each game's start time
    auto first = std::cbegin(network); // pre-C++17 std::next needs ForwardIt
    std::for_each(++first, std::cend(network), [](const int start_time) {
        std::printf("%d\n", start_time);
    });
}
