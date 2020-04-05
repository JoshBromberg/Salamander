#include "SharpCrossAI.h"
#include "IndesBody.h"
#include "Config.h"

SharpCrossAI::SharpCrossAI(glm::vec2 transform)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			IndesBody(false),
			IndesBody(false),
			IndesBody(false)
	};
#pragma endregion
	parent = new Enemy(new Frame(96, //Enemy is 96px by 288px
		build, 1, 3), 99,
		this, transform, transform.y >= Config::SCREEN_HEIGHT / 2 ? "SharpCross" : "SharpCross2");
	score = 0;
	speed.x = -5;
}

SharpCrossAI::~SharpCrossAI()
{
}

void SharpCrossAI::PrimaryFunction()
{
	if ((parent->getPosition().y < 0 || parent->getPosition().y >Config::SCREEN_HEIGHT) && speed.y == 0) {
		speed.y = parent->getPosition().y < 0 ? baseSpeed : -baseSpeed;
	}
	if (parent->getPosition().y == 144 || parent->getPosition().y == Config::SCREEN_HEIGHT - 144) {
		speed.y = -speed.y;
	}
	else if (parent->getPosition().y == -144 || parent->getPosition().y == Config::SCREEN_HEIGHT + 144) {
		speed.y == 0;
	}
}
