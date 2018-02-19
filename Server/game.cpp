#include "game.h"

Game::Game() :
	m_start(0),
	m_lastUpdate(0),
	m_usernameToPlayer(),
	m_clientIdToUsername()
{
};

Game::~Game()
{
}

bool Game::needsUpdate() 
{
	time_t currentTime = time(0);
	double deltaTime = difftime(currentTime, m_lastUpdate);

	// update every .2 seconds
	if (deltaTime > .2) {
		m_lastUpdate = currentTime;
		return true;
	}
	return false;
}

void Game::login(std::string username, unsigned __int64 serverClientId) 
{
	// remove all instances where value is username
	for (auto it = m_clientIdToUsername.cbegin(); it != m_clientIdToUsername.cend(); )
	{
		if (it->second.compare(username) == 0)
		{
			it = m_clientIdToUsername.erase(it++);  
		}
		else
		{
			++it;
		}
	}

	m_clientIdToUsername[serverClientId] = username;

	Player *newPlayerJoined = new Player(username, serverClientId);
	
	m_usernameToPlayer[username] = newPlayerJoined;
}

Player* Game::getPlayer(unsigned __int64 serverClientId)
{
	std::string username = m_clientIdToUsername[serverClientId];

	return m_usernameToPlayer[username];
}