#pragma once
#include "handler.h"
#include "terrain-navigator.h"
#include "generated\player-location_generated.h"

class PlayerLocationHandler : public Handler                      // begin declaration of the class
{
public:                      // begin public section
	PlayerLocationHandler(TerrainNavigator);       // constructor
	PlayerLocationHandler(const PlayerLocationHandler& copy_from); //copy constructor
	~PlayerLocationHandler();                    // destructor
	boost::asio::mutable_buffers_1 handle(uint8_t *buf);
private:                      // begin private section
	TerrainNavigator navigator_;
};