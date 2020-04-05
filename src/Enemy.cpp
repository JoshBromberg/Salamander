#include "Enemy.h"
#include "Game.h"
#include "FlyOntoScreenAI.h"
#include "RespawningWallAI.h"
#include "Frame.h"
#include "PlayerLockAI.h"
#include "CannonlordAI.h"
#include "ChaosAI.h"

Enemy::Enemy(){/*DANGER! Do not use!*/ }

Enemy::Enemy(Frame* enemyFrame, int enemyHealth, AI* enemyAI, glm::vec2 targetTransform, std::string enemyName):
	frame(enemyFrame), health(enemyHealth), aI(enemyAI)
{
	/*if (name == "EnemyMissile" || name == "Ram") {
		(((PlayerLockAI*)aI)->Initialize(this, 10.00f, targetTransform));
	}*/
	auto size = TheTextureManager::Instance()->getTextureSize(enemyName);
	setWidth(size.x);
	setHeight(size.y);
	frame->Initialize(this);
	setPosition(targetTransform);
	changeTexture(enemyName);
	if(name == "EnemyMissile" || name=="EnemyCannonball" || name=="EnemyFlamethrower")
	{
		setType(ENEMY_WEAPON);
	}
}

Enemy::~Enemy()
{

}

void Enemy::Damage(int i)
{
	bool doDamage = true;
	if (((RespawningWallAI*)aI)->isNotActive() && name=="RespawningWall"){
		doDamage = false;
	}
	else if (((ChaosAI*)aI)->getFire() && name=="Chaos") {
		doDamage = false;
	}
	if (doDamage && hitTimer <= 0) {
		health -= i;
		//TheGame::Instance()->destroyExplosion();
		if (health <= 0)
		{
			//std::cout << "Enemy dead: " << this->getName() << std::endl;
			TheGame::Instance()->getPlayerShip()->addScore(aI->getScore());
			TheGame::Instance()->spawnExplosion(getPosition());
			TheGame::Instance()->destroyEnemy(this);
		}
		else {
			hitTimer = hitTimerReset;
		}
	}
}

Frame* Enemy::GetFrame()
{
	return frame;
}

AI* Enemy::getAI()
{
	return aI;
}

void Enemy::Move()
{
	setPosition(getPosition() + aI->GetSpeed());
	if (health <=1 && (
		(getPosition().x + ((GetFrame()->GridWidth() * GetFrame()->getGridSize()) / 2) <= -180) ||
		(getPosition().x >= Config::SCREEN_WIDTH*1.5) ||
		(getPosition().y + ((GetFrame()->GridHeight() * GetFrame()->getGridSize()) / 2) <= -180) ||
		(getPosition().y - ((GetFrame()->GridHeight() * GetFrame()->getGridSize()) / 2) >= Config::SCREEN_HEIGHT+180)
		)) {
		TheGame::Instance()->destroyEnemy(this);
	}
}

void Enemy::draw()
{
	//std::string s = hitTimer > 0 ? name + "Hit" : name;
	if (aI->HasRotation()) {
		TheTextureManager::Instance()->draw(name, getPosition().x - (frame->getGridSize() * frame->GridWidth() / 2), getPosition().y - (frame->getGridSize() * frame->GridHeight() / 2), frame->getGridSize() * frame->GridWidth(), frame->getGridSize() * frame->GridHeight(),
			TheGame::Instance()->getRenderer(), ((FlyOntoScreenAI*)aI)->getRotation(), 255, SDL_FLIP_NONE);
	}
	else {
		TheTextureManager::Instance()->draw(name, getPosition().x-(frame->getGridSize()*frame->GridWidth()/2), getPosition().y - (frame->getGridSize() * frame->GridHeight() / 2), frame->getGridSize() * frame->GridWidth(), frame->getGridSize() * frame->GridHeight(),
			TheGame::Instance()->getRenderer());
	}
	//std::cout << name << std::endl;
}

void Enemy::update()
{
	Move();
	aI->PrimaryFunction();
	if (hitTimer > 0) {
		--hitTimer;
	}
}

void Enemy::clean()
{
}

int Enemy::getHealth()
{
	return health;
}
