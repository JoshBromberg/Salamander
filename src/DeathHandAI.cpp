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
	target = glm::vec2(Config::SCREEN_WIDTH, i == 180 ? 0 : Config::SCREEN_HEIGHT);
	score = 6000;
	isBoss = false;
	rotation = i;
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
	angle =  xDif > yDif ? acos(yDif / xDif) : acos(yDif / xDif);
	std::cout << yDif << std::endl;
	//these numbers will be wrong
	if (rotation > angle) {
		--rotation;
	}
	else if (rotation < angle) {
		++rotation;
	}
}
