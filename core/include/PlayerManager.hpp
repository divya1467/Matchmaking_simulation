#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <mutex>

#include "Matchmaker.hpp"
#include "ThreadPool.hpp"
#include "Player.hpp"

namespace core {
    class PlayerManager{
        public: 
            PlayerManager() = default;
            ~PlayerManager() = default;

            void addPlayer(std::unique_ptr<models::Player> player);
            void removePlayer(const std::string& playerId);
            models::Player* getPlayer(const std::string& playerId);
            std::vector<models::Player*> getPlayersByMode(models::GameMode mode);
            uint16_t getPlayerCount() const;
        
        private:
            std::unordered_map<std::string, std::unique_ptr<models::Player>> players;
            mutable std::mutex playerMutex;
    };
}//namespace core