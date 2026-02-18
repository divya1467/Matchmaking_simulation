#include "Matchmaker.hpp"

namespace core
{

    Matchmaker::Matchmaker(int skillTolerance)
        : skillTolerance(skillTolerance),
          matchCounter(0) {}

    void Matchmaker::addPlayer(const models::Player *player)
    {
        std::lock_guard<std::mutex> lock(matchMutex);

        waitingPools[player->getGameMode()].insert(player);

        tryCreateMatch(player->getGameMode());
    }

    void Matchmaker::tryCreateMatch(const models::GameMode &mode)
    {

        auto &pool = waitingPools[mode];
        size_t requiredPlayers = models::getTeamSize(mode);

        while (pool.size() >= requiredPlayers)
        {

            std::vector<const models::Player *> matchPlayers;

            auto it = pool.begin();
            const models::Player *firstPlayer = *it;

            int baseRating = firstPlayer->getRating();

            matchPlayers.push_back(firstPlayer);
            pool.erase(it);

            for (auto iter = pool.begin();
                 iter != pool.end() && matchPlayers.size() < requiredPlayers;)
            {

                int rating = (*iter)->getRating();

                if (rating >= baseRating - skillTolerance &&
                    rating <= baseRating + skillTolerance)
                {

                    matchPlayers.push_back(*iter);
                    iter = pool.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }

            if (matchPlayers.size() == requiredPlayers)
            {

                std::vector<models::Player> playersCopy;
                playersCopy.reserve(requiredPlayers);

                for (auto *p : matchPlayers)
                {
                    playersCopy.push_back(*p);
                }

                completedMatches.push_back(
                    models::Match{
                        mode,
                        std::move(matchPlayers)});
            }
            else
            {

                for (auto *player : matchPlayers)
                {
                    pool.insert(player);
                }

                break;
            }
        }
    }

    std::vector<models::Match> Matchmaker::getCompletedMatches()
    {

        std::lock_guard<std::mutex> lock(matchMutex);

        std::vector<models::Match> matches = completedMatches;
        completedMatches.clear();

        return matches;
    }

}