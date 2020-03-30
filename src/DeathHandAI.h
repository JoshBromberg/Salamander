#pragma once
#ifndef __DEATHHAND__
#define __DEATHHAND__
#include "FlyOntoScreenAI.h"
class DeathHandAI : public FlyOntoScreenAI
{
public:
	DeathHandAI(glm::vec2 transform, int i);
	~DeathHandAI();
	void SecondaryFunction() override;
private:
	int angle;
};
#endif