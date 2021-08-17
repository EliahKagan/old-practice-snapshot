#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

namespace {
    std::unordered_map<std::string, int> read_ballots()
    {
        std::unordered_map<std::string, int> vote_counts;

        auto ballot_count = 0;
        for (std::cin >> ballot_count; ballot_count > 0; --ballot_count) {
            std::string name;
            std::cin >> name;
            ++vote_counts[std::move(name)];
        }

        return vote_counts;
    }

    const std::string&
    find_winner(const std::unordered_map<std::string, int>& vote_counts)
    {
        using VoteCount = const std::pair<const std::string, int>&;

        const auto loses_to = [](VoteCount lhs, VoteCount rhs) noexcept {
            return lhs.second == rhs.second ? lhs.first > rhs.first
                                            : lhs.second < rhs.second;
        };

        const auto first = vote_counts.cbegin(), last = vote_counts.cend();
        const auto winner = std::max_element(first, last, loses_to);
        if (winner == last) throw std::invalid_argument{"no ballots"};

        return winner->first;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto vote_counts = read_ballots();
        std::cout << find_winner(vote_counts) << '\n';
    }
}
