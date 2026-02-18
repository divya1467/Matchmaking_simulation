#pragma once

#include <vector>

#include "Player.hpp"

namespace models {
    struct Match {
        std::string matchId;
        std::vector<Player> players;
        std::chrono::system_clock::time_point startTime;
        GameMode gameMode;
    };
}//namespace models