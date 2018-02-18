#include "stdafx.h"
#include "terrain-navigator.h"
#include "player-location.h"
#include "server.h"
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

		// create handlers
		PlayerLocationHandler plh(navigator);

		// create agents

		// start tcp and udp servers
		Server server;

		while (true) {
			if (server.HasMessages()) {
				ClientMessage message = server.PopMessage();

				const char * buffer = message.first.c_str();
				const char * identifier = flatbuffers::GetBufferIdentifier(buffer);
				
				if (std::strcmp(identifier, TransferObjects::PlayerLocationIdentifier())) {
					plh.handle(buffer);
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