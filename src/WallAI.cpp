#include "WallAI.h"
#include "IndesBody.h"
#include "Config.h"

WallAI::WallAI(glm::vec2 transform)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			IndesBody(false), IndesBody(false), IndesBody(false), IndesBody(false), IndesBody(false), IndesBody(false)
	};
#pragma endregion
	parent = new Enemy(new Frame(40, //Enemy is 240px by 40px
		build, 6, 1), 99,
		this, transform, "Wall");
	score = 0;
	speed.x = -5;
	atTarget = true;
	hasRotation = true;
	rotation = transform.y >= Config::SCREEN_HEIGHT / 2 ? 0 : 180;
	isBoss = false;
}

WallAI::~WallAI()
{
}
