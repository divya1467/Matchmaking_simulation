#include "Player.hpp"

namespace models {
    player::player(const std::string& id, int16_t rating, GameMode mode)
        : Id(id), rating(rating), gameMode(mode), joinTime(std::chrono::system_clock::now()) {}

    std::string player::getId() const { return Id; }
    int16_t player::getRating() const { return rating; }
    GameMode player::getGameMode() const { return gameMode; }
    std::chrono::system_clock::time_point player::getJoinTime() const { return joinTime; }
}//namespace models