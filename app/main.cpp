#include <iostream>
#include "PlayerManager.hpp"
#include "Matchmaker.hpp"
#include "ThreadPool.hpp"
#include "PlayerSimulator.hpp"
#include "GameMode.hpp"

int main() {
    core::PlayerManager playerManager;
    core::ThreadPool threadPool(4); 
    core::Matchmaker matchmaker(100); 

    core::PlayerSimulator simulator(playerManager, matchmaker);
    simulator.generatePlayers(100);
    matchmaker.tryCreateMatch(models::GameMode::Solo);
    threadPool.wait();
    threadPool.shutdown();

    auto matches = matchmaker.getCompletedMatches();
    std::cout << "Total matches created: " << matches.size() << "\n";
    for (const auto& match : matches) {
        std::cout << "Match in mode " 
                  << static_cast<int>(match.getGameMode())
                  << " with " << match.getPlayers().size() 
                  << " players\n";
    }

    return 0;
}