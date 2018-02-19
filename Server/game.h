#pragma once
#include <time.h>
#include <string>
#include <map>
#include <list>
#include "player.h"

class Game {
public:
	Game();
	~Game();

	bool needsUpdate();
	void login(std::string username, unsigned __int64 serverClientId);

	Player* getPlayer(unsigned __int64 serverClientId);
	inline std::map<std::string, Player *> getPlayerMap() { return m_usernameToPlayer; };
private:
	Game(Game&);

	time_t m_start;
	time_t m_lastUpdate;

	std::map<unsigned __int64, std::string> m_clientIdToUsername;
	std::map<std::string, Player *> m_usernameToPlayer;

};