#pragma once
#ifndef __TETRANARM__
#define __TETRANARM__
#include "TetranAI.h"
class TetranArmAI : public TetranAI
{
public:
	TetranArmAI(glm::vec2 transform, int r);
	~TetranArmAI();
	void SecondaryFunction() override;
private:
	int firingCooldown = 0, firingCooldownReset = 60;
};
#endif