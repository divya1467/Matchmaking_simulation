#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include <mutex>
#include "models/Player.hpp"
#include "models/Match.hpp"

namespace core {

class Matchmaker {
public:
    Matchmaker(size_t playersPerMatch, int skillTolerance);

    void addPlayer(const Player& player);
    std::vector<Match> getCompletedMatches();

private:
    void tryCreateMatch(const std::string& mode);

    size_t playersPerMatch;
    int skillTolerance;
    int matchCounter;

    std::unordered_map<
        std::string,
        std::multiset<Player, SkillComparator>
    > waitingPools;

    std::vector<Match> completedMatches;

    std::mutex matchMutex;
};

}
