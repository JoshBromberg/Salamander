#pragma once
#ifndef __SHARPCROSS__
#define __SHARPCROSS__
#include "AI.h"
class SharpCrossAI : public AI
{
public:
	SharpCrossAI(glm::vec2 transform);
	~SharpCrossAI();
	void PrimaryFunction() override;
private:
	int i = 0, baseSpeed = 8;
};
#endif