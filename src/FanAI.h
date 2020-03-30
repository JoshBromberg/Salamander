#pragma once
#ifndef __FAN__
#define __FAN__
#include "FlyOntoScreenAI.h"
#include "Game.h"
class FanAI : public FlyOntoScreenAI
{
public:
	FanAI(glm::vec2 transform, int i);
	~FanAI();
	void SecondaryFunction() override;
private:
	int yDirection, phase = 0, baseSpeed = 6;
	glm::vec2 target1 = { Config::SCREEN_WIDTH*0.75, Config::SCREEN_HEIGHT/2 }, target2;
};
#endif