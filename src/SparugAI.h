#pragma once
#ifndef __SPARUG__
#define __SPARUG__
#include "FlyOntoScreenAI.h"
class SparugAI : public FlyOntoScreenAI
{
public:
	SparugAI(glm::vec2 transform);
	~SparugAI();
	void SecondaryFunction() override;
private:
	int firingCooldown = 60, firingCooldownReset = 60;
};
#endif