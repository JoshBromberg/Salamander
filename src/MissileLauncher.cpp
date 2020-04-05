#include "MissileLauncher.h"
#include "Game.h"
#include "EnemyMissileAI.h"

MissileLauncher::MissileLauncher()
{
	name = "MissileLauncher";
}

MissileLauncher::~MissileLauncher()
{
}

void MissileLauncher::Fire()
{
		TheGame::Instance()->spawnEnemy(new EnemyMissileAI(getPosition()));
}

void MissileLauncher::Fire(glm::vec2 trajectory)
{
	if (getParent()->getParent()->getName() != "Player") {
		TheGame::Instance()->spawnEnemy(new EnemyMissileAI(getPosition(), getPosition() + trajectory));
	}
}


