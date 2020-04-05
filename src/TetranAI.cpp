#include "TetranAI.h"
#include "IndesBody.h"
#include "BasicBody.h"
#include "Blank.h"
#include "Config.h"
#include "Vector2.h"

TetranAI::TetranAI()
{
}

TetranAI::TetranAI(glm::vec2 transform)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			Blank(),			Blank(),			Blank(),			IndesBody(false),	Blank(),			Blank(),
			IndesBody(false),	IndesBody(false),	IndesBody(false),	IndesBody(false),	IndesBody(false),	IndesBody(false),
			Blank(),			Blank(),			Blank(),			BasicBody(),		IndesBody(false),	Blank(),
			Blank(),			Blank(),			Blank(),			BasicBody(),		IndesBody(false),	Blank(),
			IndesBody(false),	IndesBody(false),	IndesBody(false),	IndesBody(false),	IndesBody(false),	IndesBody(false),
			Blank(),			Blank(),			Blank(),			IndesBody(false),	Blank(),			Blank()
	};
#pragma endregion
	parent = new Enemy(new Frame(45, //Enemy is 270px by 270px
		build, 6, 6), 10,
		this, transform, "Tetran");
	score = 90000;
	target = { transform.x - 655, transform.y};
}

TetranAI::~TetranAI()
{
}

void TetranAI::SecondaryFunction()
{
	i+=3;
	if (i >= 360) {
		i -= 360;
	}
	float ir = i * M_PI / 180;
	Vector2 spd = { cos(ir) * baseSpeed.x, sin(ir) * baseSpeed.y };
	speed = { spd.x, spd.y };
}
