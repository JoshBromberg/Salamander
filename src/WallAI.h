#pragma once
#ifndef __WALL__
#define __WALL__
#include "FlyOntoScreenAI.h"
class WallAI : public FlyOntoScreenAI
{
public:
	WallAI(glm::vec2 transform);
	~WallAI();
};
#endif