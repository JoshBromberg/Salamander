#include "TetranArmAI.h"
#include "Blank.h"
#include "IndesBody.h"
#include "MissileLauncher.h"
#include "Config.h"

TetranArmAI::TetranArmAI(glm::vec2 transform, int r)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			Blank(),
			Blank(),
			Blank(),
			Blank(),
			Blank(),
			Blank(),
			Blank(),
			IndesBody(false),
			IndesBody(false),
			IndesBody(false),
			MissileLauncher()
	};
#pragma endregion
	parent = new Enemy(new Frame(60, //Enemy is 60px by 660px
		build, 1, 11), 99,
		this, transform, "TetranArm");
	score = 0;
	hasRotation = true;
	rotation = r;
	target = { transform.x - 655, transform.y };
}

TetranArmAI::~TetranArmAI()
{
}

void TetranArmAI::SecondaryFunction()
{
	TetranAI::SecondaryFunction();
	rotation+=5;
	if (rotation >= 360) {
		rotation -= 360;
	}
	--firingCooldown;
	if (firingCooldown <= 0) {
		firingCooldown = firingCooldownReset;
		for (Weapon w : parent->GetFrame()->GetWeapons()) {
			w.Fire();
		}
	}
}
