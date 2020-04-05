#include "RespawningWallAI.h"
#include "BasicBody.h"

RespawningWallAI::RespawningWallAI(glm::vec2 transform)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			BasicBody()
	};
#pragma endregion
	lastHealth = 99;
	parent = new Enemy(new Frame(40, //Enemy is 40px by 40px
		build, 1, 1), lastHealth,
		this, transform, "RespawningWall");
	score = 0;
	speed.x = -5;
}

RespawningWallAI::~RespawningWallAI()
{
}

void RespawningWallAI::PrimaryFunction()
{
	if (respawnTimer > 0) {
		--respawnTimer;
		if (respawnTimer <= 0) {
			active = true;
		}
	}
	if (parent->getHealth() < lastHealth) {
		lastHealth = parent->getHealth();
		active = false;
		respawnTimer = respawnTimerReset;
		std::cout << "ran!" << std::endl;
	}
}

bool RespawningWallAI::isActive()
{
	return active;
}

bool RespawningWallAI::isNotActive()
{
	return active ? false : true; //subject for removal
}
