#include "SparugAI.h"
#include "MissileLauncher.h"
#include "Config.h"

SparugAI::SparugAI(glm::vec2 transform)
{
	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
			MissileLauncher()
	};
#pragma endregion
	parent = new Enemy(new Frame(40, //Enemy is 40px by 40px
		build, 1, 1), 1,
		this, transform, "Sparug");
	score = 900;
	circle = true;
	speed.x = -5;
	atTarget = true;
	rotation = (transform.y >= Config::SCREEN_HEIGHT / 2 || transform.y == Config::SCREEN_HEIGHT / 2 - 30) && transform.y != Config::SCREEN_HEIGHT / 2 + 30 ? 0 : 180;
	hasRotation = true;
}

SparugAI::~SparugAI()
{
}

void SparugAI::SecondaryFunction()
{
	--firingCooldown;
	if (firingCooldown <= 0) {
		firingCooldown = firingCooldownReset;
		for (Weapon w : parent->GetFrame()->GetWeapons()) {
			w.Fire();
		}
	}
}
