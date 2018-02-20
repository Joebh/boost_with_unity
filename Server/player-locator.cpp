#include "player-locator.h"

PlayerLocator::PlayerLocator()
{
}

PlayerLocator::~PlayerLocator()
{

}

std::list<Player *> PlayerLocator::findClosePlayers(Player *player, std::list<Player *>& closePlayers, std::map<std::string, Player *> playerMap)
{
	closePlayers.empty();

	// iterate over all players adding them all
	for (auto it = playerMap.cbegin(); it != playerMap.cend(); it++)
	{
		if (it->second == player) {
			continue;
		}
		else {
			closePlayers.push_front(it->second);
		}
	}

	return closePlayers;
}