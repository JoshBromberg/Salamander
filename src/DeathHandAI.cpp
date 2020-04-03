#include "DeathHandAI.h"
#include "BasicBody.h"
#include "IndesBody.h"
#include "Blank.h"
#include "Game.h"

DeathHandAI::DeathHandAI(glm::vec2 transform, int i)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			IndesBody(false),
			IndesBody(false),
			BasicBody(),
			IndesBody(false),
			Blank(),
			Blank(),
			Blank(),
			Blank()
	};
#pragma endregion
	parent = new Enemy(new Frame(40, //Enemy is 40px by 160px
		build, 1, 8), 1,
		this, transform, "DeathHand");
	entrySpeed = { -5, i == 180 ? 10 : -10 };
	target = transform.y > 0 && transform.y <Config::SCREEN_HEIGHT ? glm::vec2(Config::SCREEN_WIDTH, i == 180 ? Config::SCREEN_HEIGHT / 2 - 160 : Config::SCREEN_HEIGHT / 2 + 160) : glm::vec2(Config::SCREEN_WIDTH, i == 180 ? 0 : Config::SCREEN_HEIGHT);
	score = 6000;
	if (i == 0) { i = 360; }
	rotation = i;
	hasRotation = true;
	speed.x = -5;
}

DeathHandAI::~DeathHandAI()
{
}

void DeathHandAI::SecondaryFunction()
{
	float tX = TheGame::Instance()->getPlayerPosition().x;
	float tY = TheGame::Instance()->getPlayerPosition().y;
	float xDif = abs(GetParent()->getPosition().x - tX), yDif = abs(GetParent()->getPosition().y - tY);
	double a =  xDif > yDif ? yDif / xDif : xDif / yDif;
	a = xDif > yDif ? acos(a) * 180 / M_PI : asin(a) * 180 / M_PI;
	a = GetParent()->getPosition().x > tX ? a : -a;
	angle = GetParent()->getPosition().y <= Config::SCREEN_HEIGHT / 2 ? 180 + a: 360 - a;
	if (rotation > angle) {
		--rotation;
	}
	else if (rotation < angle) {
		++rotation;
	}
}
