#pragma once
#include <boost/asio.hpp>
#include "flatbuffers\flatbuffers.h"

class Handler                      // begin declaration of the class
{
public:                      // begin public section
	Handler();       // constructor
	virtual ~Handler();                    // destructor
	virtual boost::asio::mutable_buffers_1 handle(uint8_t *buf);
private:                      // begin private section
};