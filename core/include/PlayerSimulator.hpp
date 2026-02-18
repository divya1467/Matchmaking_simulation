#pragma once

#include <random>
#include "Matchmaker.hpp"
#include "ThreadPool.hpp"
#include "PlayerManager.hpp"

namespace core {
    class PlayerSimulator {
    public:
        PlayerSimulator(PlayerManager& playerManager, Matchmaker& matchmaker);
        void generatePlayers(size_t count);

    private:
        PlayerManager& playerManager;
        Matchmaker& matchmaker;
        std::mt19937 rng;
        std::uniform_int_distribution<int16_t> ratingDist;
        std::uniform_int_distribution<int> modeDist;

    };
}//namespace core