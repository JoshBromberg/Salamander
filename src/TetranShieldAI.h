#pragma once
#ifndef __TETRANSHIELD__
#define __TETRANSHIELD__
#include "TetranAI.h"
class TetranShieldAI : public TetranAI
{
public:
	TetranShieldAI(glm::vec2 transform);
	~TetranShieldAI();
};
#endif