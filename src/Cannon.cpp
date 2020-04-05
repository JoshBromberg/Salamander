#include "Cannon.h"
#include "Cannonball.h"
#include "Game.h"
Cannon::Cannon()
{
	name = "Cannon";
}

Cannon::~Cannon()
{
}

void Cannon::Fire()
{

	if (getParent()->getParent()->getName() == "Player")
	{
		glm::vec2 velocity;
		int y = getID().y;

		switch (y)
		{
		case 0:

			velocity = glm::vec2(4.0, -4.0f);
			break;

		case 1:

			velocity = glm::vec2(8.0f, 0.0f);
			break;

		case 2:

			velocity = glm::vec2(4.0f, 4.0f);
			break;
		}
		TheGame::Instance()->spawnPlayerWeapon(new Cannonball(getPosition(), velocity));
	}

}
void Cannon::Fire(Vector2 direction)
{

}
