#pragma once
#ifndef __RESPAWNINGWALL__
#define __RESPAWNINGWALL__
#include "AI.h"
class RespawningWallAI : public AI
{
public:
	RespawningWallAI(glm::vec2 transform);
	~RespawningWallAI();
	void PrimaryFunction() override;
	bool isActive();
	bool isNotActive();
private:
	int respawnTimer = 0, respawnTimerReset = 180, lastHealth;
	bool active = true;
};
#endif