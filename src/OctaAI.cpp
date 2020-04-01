#include "OctaAI.h"
#include "BasicBody.h"
#include "CollisionManager.h"
#include "Config.h"

OctaAI::OctaAI(glm::vec2 transform)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			BasicBody()
	};
#pragma endregion
	parent = new Enemy(new Frame(40, //Enemy is 40px by 40px
		build, 1, 1), 1,
		this, transform, "Octa");
	score = 240;
	circle = true;
	speed.x = -baseSpeed;
}

OctaAI::~OctaAI()
{
}

void OctaAI::PrimaryFunction()
{
	i+=3;
	speed.y = sin(i * M_PI / 180) * baseSpeed;
}
