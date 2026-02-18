#include "Matchmaker.hpp"

namespace core{
   Matchmaker(size_t playersPerMatch, int skillTolerance):
    playersPerMatch(playersPerMatch),
    skillTolerance(skillTolerance),
    matchCounter(0) {}

    void Matchmaker::addPlayer(const Player& player) {
        std::lock_guard<std::mutex> lock(matchMutex);
        waitingPools[player.gameMode].insert(player);
        tryCreateMatch(std::to_string(static_cast<int>(player.gameMode)));
    }

    void Matchmaker::tryCreateMatch(const std::string& mode) {
        auto& pool = waitingPools[mode];
        while (pool.size() >= playersPerMatch) {
            std::vector<Player> matchPlayers;
            auto it = pool.begin();
            matchPlayers.push_back(*it);
            pool.erase(it);

            for (size_t i = 1; i < playersPerMatch; ++i) {
                it = pool.lower_bound(Player{"", matchPlayers[0].rating - skillTolerance, static_cast<GameMode>(std::stoi(mode)), std::chrono::system_clock::now()});
                if (it == pool.end() || it->rating > matchPlayers[0].rating + skillTolerance) {
                    break;
                }
                matchPlayers.push_back(*it);
                pool.erase(it);
            }

            if (matchPlayers.size() == playersPerMatch) {
                completedMatches.push_back(Match{
                    "match_" + std::to_string(matchCounter++),
                    matchPlayers,
                    std::chrono::system_clock::now(),
                    static_cast<GameMode>(std::stoi(mode))
                });
            } else {
                for (const auto& player : matchPlayers) {
                    pool.insert(player);
                }
                break;
            }
        }
    }
}