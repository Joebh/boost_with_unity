#include <iostream>            // for cout and cin
#include "handler.h"

// constructor of TerrainNavigator,
Handler::Handler()
{
}

// destructor, just an example
Handler::~Handler()
{

}

boost::asio::mutable_buffers_1 Handler::handle(uint8_t *buf) {
	boost::asio::mutable_buffers_1 buffer("", 1);
	return buffer;
}