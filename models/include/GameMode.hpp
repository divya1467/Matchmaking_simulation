#pragma once
#include <cstddef>

namespace models {
    enum class GameMode{
        Solo,
        Duo,
        Squad
    };
    
    inline constexpr std::size_t getTeamSize(GameMode mode) {
        switch (mode) {
            case GameMode::Solo: return 1;
            case GameMode::Duo: return 2;
            case GameMode::Squad: return 4;
            default: return 1;
        }
    }


}