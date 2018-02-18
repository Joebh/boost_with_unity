#pragma once
#include <time.h>
#include <string>
#include <map>
#include "player.h"

class Game {
public:
	Game();
	~Game();

	bool needsUpdate();
	void login(std::string username, unsigned __int64 serverClientId);

	Player& getPlayer(unsigned __int64 serverClientId);
private:
	Game(Game&);

	time_t m_start;
	time_t m_lastUpdate;

	std::map<__int64, std::string> m_clientIdToUsername;
	std::map<std::string, Player> m_usernameToPlayer;
};