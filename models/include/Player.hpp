#pragma once

#include <string>
#include <chrono>

#include "GameMode.hpp"

namespace models {


    class Player {
    public:
        Player(const std::string& id, int16_t rating, GameMode mode);

        std::string getId() const;
        int16_t getRating() const;
        GameMode getGameMode() const;
        std::chrono::system_clock::time_point getJoinTime() const;

    private:
        std::string Id;
        int16_t rating;
        GameMode gameMode;
        std::chrono::system_clock::time_point joinTime;
    };


    struct skillComparator {
        bool operator()(const Player* a, const Player* b) const {
            if (a->getRating() == b->getRating()) {
            return a->getId() < b->getId(); // tie-breaker
        }
            return a->getRating() < b->getRating();
        }
    };

}
//namespace models
