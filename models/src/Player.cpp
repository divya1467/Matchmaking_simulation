#include "Player.hpp"

namespace models {
    
    Player::Player(const std::string& id, int16_t rating, GameMode mode)
        : Id(id), rating(rating), gameMode(mode), joinTime(std::chrono::system_clock::now()) {}

    std::string Player::getId() const { return Id; }
    int16_t Player::getRating() const { return rating; }
    GameMode Player::getGameMode() const { return gameMode; }
    std::chrono::system_clock::time_point Player::getJoinTime() const { return joinTime; }
}//namespace models