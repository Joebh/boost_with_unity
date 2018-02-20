#pragma once
#include "player.h"
#include <list>
#include <map>

class PlayerLocator {
public:
	PlayerLocator();
	~PlayerLocator();

	std::list<Player *> findClosePlayers(Player *, std::list<Player *>& closePlayers, std::map<std::string, Player *>);
private:
	
};