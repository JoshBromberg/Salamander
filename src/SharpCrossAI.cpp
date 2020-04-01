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
		build, 1, 3), 1,
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
	else if ((parent->getPosition().y >= 144 && parent->getPosition().y <= Config::SCREEN_HEIGHT - 144)) {
		
		bool first = false;
		if (i == 0) {
			first = true;
		}
		i += baseSpeed;
		if (i >= 288 || i<=abs(baseSpeed) && !first) {
			speed.y = -speed.y;
			baseSpeed = -baseSpeed;
		}
	}
	else if (baseSpeed < 0 && i<=0) {
		speed.y = -speed.y;
		baseSpeed = -baseSpeed;
		i += baseSpeed;
	}
}
