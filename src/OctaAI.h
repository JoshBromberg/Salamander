#pragma once
#ifndef __OCTA__
#define __OCTA__
#include "AI.h"
class OctaAI : public AI
{
public:
	OctaAI(glm::vec2 transform);
	~OctaAI();
	void PrimaryFunction() override;
private:
	int i = 0, baseSpeed = 6;
};
#endif