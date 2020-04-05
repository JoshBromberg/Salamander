#include "TetranShieldAI.h"
#include "BasicBody.h"

TetranShieldAI::TetranShieldAI(glm::vec2 transform)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
		BasicBody(),
		BasicBody(),
		BasicBody()
	};
#pragma endregion
	parent = new Enemy(new Frame(30, //Enemy is 30px by 90px
		build, 1, 3), 3,
		this, transform, "TetranShield");
	score = 0;
	target = { transform.x - 655, transform.y };
	isBoss = false;
}

TetranShieldAI::~TetranShieldAI()
{
}
