#pragma once
#ifndef __TETRAN__
#define __TETRAN__
#include "FlyOntoScreenAI.h"
class TetranAI : public FlyOntoScreenAI
{
public:
	TetranAI();
	TetranAI(glm::vec2 transform);
	~TetranAI();
	void SecondaryFunction() override;
private:
	glm::vec2 baseSpeed = { 5, 3 };
	int i = 90;
};
#endif