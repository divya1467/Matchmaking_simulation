#pragma once

#include <string>
#include <chrono>

namespace models {
    enum class GameMode{
        Solo,
        Duo,
        Squad
    };

    struct Player {
        std::string Id;
        int16_t rating;
        GameMode gameMode;
        std::chrono::system_clock::time_point joinTime;
    };

    struct skillComparator {
        bool operator()(const Player& a, const Player& b) const {
            if (a.rating == b.rating) {
            return a.Id < b.Id; // tie-breaker
        }
            return a.rating < b.rating;
        }
    };

    class player {
    public:
        player(const std::string& id, int16_t rating, GameMode mode)
            : Id(id), rating(rating), gameMode(mode), joinTime(std::chrono::system_clock::now()) {}

        std::string getId() const { return Id; }
        int16_t getRating() const { return rating; }
        GameMode getGameMode() const { return gameMode; }
        std::chrono::system_clock::time_point getJoinTime() const { return joinTime; }

    private:
        std::string Id;
        int16_t rating;
        GameMode gameMode;
        std::chrono::system_clock::time_point joinTime;
    }




}
//namespace models
