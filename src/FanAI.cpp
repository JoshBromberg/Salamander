#include "FanAI.h"
#include "BasicBody.h"

FanAI::FanAI(glm::vec2 transform, int i)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			BasicBody()
	};
#pragma endregion
	parent = new Enemy(new Frame(40, //Enemy is 80px by 80px
		build, 1, 1), 1,
		this, transform, "Fan");
	target = glm::vec2(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT/2);
	score = 180;
	yDirection = i < 0 ? -1 : 1;
	target2 = { Config::SCREEN_WIDTH * 0.8, i == 1 ? Config::SCREEN_HEIGHT * 0.67 : Config::SCREEN_HEIGHT * 0.33 };
	isBoss = false;
}

FanAI::~FanAI()
{
}

void FanAI::SecondaryFunction()
{
	if (atTarget && phase < 3) {
		++phase;
		atTarget = false;
		switch (phase) {
		case 1:
			target = target1;
			entrySpeed.x = -baseSpeed;
			break;
		case 2:
			backTarget = true;
			target = target2;
			entrySpeed.y = baseSpeed * yDirection;
			entrySpeed.x = baseSpeed / 3;
			break;
		case 3:
			entrySpeed.x = -baseSpeed;
			entrySpeed.y = 0;
			target = { -500, parent->getPosition().y };
			backTarget = false;
			break;
		}
	}
}
