#include <PlayerManager.hpp>

namespace core {
    
    void PlayerManager::addPlayer(std::unique_ptr<models::Player> player) {
        std::lock_guard<std::mutex> lock(playerMutex);
        players[player->getId()] = std::move(player);
    }

    void PlayerManager::removePlayer(const std::string& playerId) {
        std::lock_guard<std::mutex> lock(playerMutex);
        players.erase(playerId);
    }

    models::Player* PlayerManager::getPlayer(const std::string& playerId) {
        std::lock_guard<std::mutex> lock(playerMutex);
        auto it = players.find(playerId);
        return it != players.end() ? it->second.get() : nullptr;
    }

    std::vector<models::Player*> PlayerManager::getPlayersByMode(models::GameMode mode) {
        std::vector<models::Player*> result;
        std::lock_guard<std::mutex> lock(playerMutex);
        for (auto& pair : players) {
            if (pair.second->getGameMode() == mode) {
                result.push_back(pair.second.get());
            }
        }
        return result;
    }

    uint16_t PlayerManager::getPlayerCount() const {
        std::lock_guard<std::mutex> lock(playerMutex);
        return static_cast<uint16_t>(players.size());
    }
}//namespace core