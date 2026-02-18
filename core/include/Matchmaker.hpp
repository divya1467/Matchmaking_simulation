#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include <mutex>
#include <Player.hpp>
#include <Match.hpp>

namespace core {

class Matchmaker {
public:
    Matchmaker(int skillTolerance);

    void addPlayer(const models::Player* player);
    std::vector<models::Match> getCompletedMatches();
    void tryCreateMatch(const models::GameMode& mode);

private:

    int skillTolerance;
    int matchCounter;

    std::unordered_map<
        models::GameMode,
        std::multiset<const models::Player*, models::skillComparator>
    > waitingPools;

    std::vector<models::Match> completedMatches;

    std::mutex matchMutex;
};

}
