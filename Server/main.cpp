#include "stdafx.h"
#include "terrain-navigator.h"
#include "player-location.h"
#include "player-login.h"
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

		// create handlers
		PlayerLocationHandler playerLocationHandler(navigator, &game);
		PlayerLoginHandler loginHandler(&game);

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
				if (flatbuffers::BufferHasIdentifier(buffer, TransferObjects::PlayerLocationIdentifier())) {
					Player player = game.getPlayer(clientId);
					playerLocationHandler.handle(buffer, player);

					std::string updateLocation = player.toBinary();

					server.SendToClient(updateLocation, clientId);
				}

				if (flatbuffers::BufferHasIdentifier(buffer, TransferObjects::PlayerLoginIdentifier())) {
					loginHandler.handle(buffer, clientId);
				}
			}

			// if need up date
			//if (game.needsUpdate()) {
			//	// for each client
			//	auto ids = server.getClientIds();

			//	for (auto clientId : ids) {
			//		Player *player = game.getPlayer(clientId);
			//		std::string updateLocation = player->toBinary();

			//		server.SendToClient(updateLocation, clientId);
			//	}
			//	
			//	// send data coordisponding to what that client should see
			//}

		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}