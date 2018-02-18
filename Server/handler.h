#pragma once
#include "flatbuffers\flatbuffers.h"

class Handler                      // begin declaration of the class
{
public:                      // begin public section
	Handler();       // constructor
	virtual ~Handler();                    // destructor
	virtual void handle(const void *buf);
private:                      // begin private section
};