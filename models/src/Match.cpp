#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "Match.hpp"

namespace models {

Match::Match(GameMode mode, std::vector<const Player*> players)
    : gameMode(mode), players(std::move(players)) {}

GameMode Match::getGameMode() const {
    return gameMode;
}

const std::vector<const Player*>& Match::getPlayers() const {
    return players;
}

void Match::startMatch() {
    std::cout << "Match started with "
              << players.size()
              << " players.\n";

    // Simulate match running
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Match ended.\n";
}

} // namespace models