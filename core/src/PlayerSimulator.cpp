#include <PlayerSimulator.hpp>

namespace core
{
    PlayerSimulator::PlayerSimulator(PlayerManager &playerManager, Matchmaker &matchmaker)
        : playerManager(playerManager), matchmaker(matchmaker), rng(std::random_device{}()),
          ratingDist(0, 3000), modeDist(0, 2) {}

    void PlayerSimulator::generatePlayers(size_t count)
    {
        for (size_t i = 0; i < count; ++i)
        {
            auto mode = static_cast<models::GameMode>(modeDist(rng));
            std::string id = "Player" + std::to_string(i);
            int16_t rating = ratingDist(rng);
            auto player = std::make_unique<models::Player>(id, rating, mode);
            models::Player *playerPtr = player.get();
            playerManager.addPlayer(std::move(player));

            matchmaker.addPlayer(playerPtr);
        }
    }
} // namespace core