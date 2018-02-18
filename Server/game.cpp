#include "game.h"

Game::Game() :
	m_start(0),
	m_lastUpdate(0),
	m_clientIdToUsername(),
	m_usernameToPlayer()
{
	Player test("joe");

	m_usernameToPlayer["joe"] = test;
};

Game::~Game()
{
}

bool Game::needsUpdate() 
{
	time_t currentTime(0);
	double deltaTime = difftime(currentTime, m_lastUpdate);

	// update every .2 seconds
	if (deltaTime < .2) {
		m_lastUpdate = currentTime;
		return true;
	}
}

void Game::login(std::string username, unsigned __int64 serverClientId) 
{
	m_clientIdToUsername[serverClientId] = username;
}

Player& Game::getPlayer(unsigned __int64 serverClientId)
{
	//std::string username = m_clientIdToUsername.at(serverClientId);
	return m_usernameToPlayer.at("joe");
}