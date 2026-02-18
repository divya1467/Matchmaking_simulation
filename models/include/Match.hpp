#pragma once

#include <vector>
#include <cstddef>

#include <Player.hpp>
#include <GameMode.hpp>

namespace models {

class Match {
public:
    Match(GameMode mode, std::vector<const Player*> players);

    GameMode getGameMode() const;

    const std::vector<const Player*>& getPlayers() const;

    void startMatch();

private:
    GameMode gameMode;

    std::vector<const Player*> players;
};

} // namespace models