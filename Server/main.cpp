#include "stdafx.h"
#include "terrain-navigator.h"
#include "player-handler.h"
#include "player-login-handler.h"
#include "player-locator.h"
#include "server.h"
#include "game.h"
#include <iostream>

int main()
{
	try
	{
		// call db for state of game
		// load previous player locations

		// load terrain
		TerrainNavigator navigator;

		navigator.loadMesh("terrain.navmesh");

		// create game object that holds all shared data
		Game game;

		// create handlers to deal with incoming messages
		PlayerHandler playerHandler(navigator, &game);
		PlayerLoginHandler loginHandler(&game);

		PlayerLocator playerLocator;

		// create agents

		// start udp server
		Server server;

		while (true) {
			// handle all server messages
			if (server.HasMessages()) {
				ClientMessage message = server.PopMessage();

				const char * buffer = message.first.c_str();
				unsigned __int64 clientId = message.second;

				//const char * identifier = flatbuffers::GetBufferIdentifier(buffer);
				
				// a player updated his location, update it in the game object
				if (flatbuffers::BufferHasIdentifier(buffer, TransferObjects::PlayerIdentifier())) {
					Player *player = game.getPlayer(clientId);
					playerHandler.handle(buffer, player);
				}

				if (flatbuffers::BufferHasIdentifier(buffer, TransferObjects::PlayerLoginIdentifier())) {
					std::string successMessage = loginHandler.handle(buffer, clientId);

					server.SendToClient(successMessage, clientId);
				}
			}

			// if need up date
			if (game.needsUpdate()) {
				// for each logged in player
				std::map<std::string, Player *> playerMap = game.getPlayerMap();

				for (auto playerPair : playerMap) {
					Player *player = playerPair.second;
					
					std::list<Player *> closePlayers = player->getClosePlayers();
					playerLocator.findClosePlayers(player, closePlayers, playerMap);

					std::string playerData = playerHandler.toBinary(player);
					server.SendToClient(playerData, player->getClientId());

					for (Player *closePlayer : closePlayers) {
						std::string playerData = playerHandler.toBinary(closePlayer);
						server.SendToClient(playerData, player->getClientId());
					}
				}
			}

		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}