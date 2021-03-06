#include "LevelScene.h"
#include "FanAI.h"
#include "DeathHandAI.h"
#include "OctaAI.h"
#include "SharpCrossAI.h"
#include "SparugAI.h"
#include "RespawningWallAI.h"
#include "WallAI.h"
#include "TetranAI.h"
#include "TetranShieldAI.h"
#include "TetranArmAI.h"
#include "BasicBody.h"
#include "IndesBody.h"
#include "CollisionManager.h"
#include <experimental/coroutine>
#include "Game.h"
#include "FlyOntoScreenAI.h"
#include "Scoreboard.h"

LevelScene::LevelScene()
{

}

LevelScene::~LevelScene()
{
	
}

void LevelScene::update()
{
	++time;
	spawnedEnemy = false;
	initialize();
	if (player->getPlayerLives() >= 0)
	{
		player->update();
	}
	if (m_pMap != nullptr)
	{
		m_pMap->update();
	}
	if (m_pMap2 != nullptr)
	{
		m_pMap2->update();
	}
	for (int z = 0; z < enemies.size(); ++z) {
		enemies[z]->GetParent()->update();
	}
	for (PlayerWeapon* pw : playerWeapons)
		{
			pw->update();
		}
	#pragma region Collisions
	//if the enemies are spawned or if the player is not invincible
	if (!playerWeapons.empty() || !player->getInvincibility()) {
		for (AI* enemy : enemies) {
			if (!playerWeapons.empty()) {
				for (PlayerWeapon* pw : playerWeapons) {
					collisionCheck(((FlyOntoScreenAI*)enemy)->isBoss, enemy, pw);
				}
			}
			if (!player->getInvincibility()) {
				collisionCheck(((FlyOntoScreenAI*)enemy)->isBoss, enemy);
			}
		}
	}
	#pragma endregion
	
	#pragma region Spawn Enemies
	if (fanIteration < fanSpawnTimer.size()) {
		if (time == fanSpawnTimer[fanIteration])
		{
			spawnEnemy(new FanAI(fanSpawnLocation[fanIteration], (fanIteration / 5) % 2 == 0 ? 1 : -1));
			++fanIteration;
		}
	}
	if (deathHandIteration < deathHandSpawnTimer.size()) {
		if (time == deathHandSpawnTimer[deathHandIteration])
		{
			spawnEnemy(new DeathHandAI(deathHandSpawnLocation[deathHandIteration], deathHandSpawnLocation[deathHandIteration].y < Config::SCREEN_HEIGHT/2 ? 180 : 0));
			++deathHandIteration;
		}
	}
	if (octaIteration < octaSpawnTimer.size()) {
		if (time == octaSpawnTimer[octaIteration])
		{
			spawnEnemy(new OctaAI(octaSpawnLocation[octaIteration]));
			++octaIteration;
		}
	}
	if (sharpCrossIteration < sharpCrossSpawnTimer.size()) {
		if (time == sharpCrossSpawnTimer[sharpCrossIteration])
		{
			spawnEnemy(new SharpCrossAI(sharpCrossSpawnLocation[sharpCrossIteration]));
			++sharpCrossIteration;
		}
	}
	if (sparugIteration < sparugSpawnTimer.size()) {
		if (time == sparugSpawnTimer[sparugIteration])
		{
			spawnEnemy(new SparugAI(sparugSpawnLocation[sparugIteration]));
			++sparugIteration;
		}
	}
	if (respawningWallIteration < respawningWallTimer.size()) {
		if (time == respawningWallTimer[respawningWallIteration])
		{
			spawnEnemy(new RespawningWallAI(respawningWallSpawnLocation[respawningWallIteration]));
			++respawningWallIteration;
		}
	}
	if (time >= 1776 && time <= 6800 && time % 48 == 0) {
		spawnEnemy(new WallAI({Config::SCREEN_WIDTH+120, 20}));
	}
	else if (time >= 1777 && time <=6800 && time % 48 == 1) {
		spawnEnemy(new WallAI({ Config::SCREEN_WIDTH + 120, Config::SCREEN_HEIGHT - 20 }));
	}
	/*if (time < 6999)
		time = 6999;*/
	if (time == 7000 && !bossActive) {
		bossActive = true;
		playSound("Boss", 999);
		spawnEnemy(new TetranArmAI({ Config::SCREEN_WIDTH + 255, Config::SCREEN_HEIGHT / 2 }, 45));
		spawnEnemy(new TetranArmAI({ Config::SCREEN_WIDTH + 255, Config::SCREEN_HEIGHT / 2 }, 135));
		spawnEnemy(new TetranArmAI({ Config::SCREEN_WIDTH + 255, Config::SCREEN_HEIGHT / 2 }, 225));
		spawnEnemy(new TetranArmAI({ Config::SCREEN_WIDTH + 255, Config::SCREEN_HEIGHT / 2 }, 315));
		spawnEnemy(new TetranShieldAI({ Config::SCREEN_WIDTH + 150, Config::SCREEN_HEIGHT / 2 }));
		spawnEnemy(new TetranShieldAI({ Config::SCREEN_WIDTH + 180, Config::SCREEN_HEIGHT / 2 }));
		spawnEnemy(new TetranShieldAI({ Config::SCREEN_WIDTH + 210, Config::SCREEN_HEIGHT / 2 }));
		spawnEnemy(new TetranShieldAI({ Config::SCREEN_WIDTH + 240, Config::SCREEN_HEIGHT / 2 }));
		spawnEnemy(new TetranAI({ Config::SCREEN_WIDTH + 255, Config::SCREEN_HEIGHT / 2 }));
	}

	#pragma endregion

	if(player->getPlayerLives() < 0)
	{
		Game::Instance()->changeSceneState(END_SCENE);
	}

#pragma region Garbage collection for animated explosions
	if(garbage.size() > 10 || time % 1000 == 0)
	{
		//std::cout << "Gabage collection is implemented\n";
		removeGarbage();
	}
#pragma endregion
}

void LevelScene::draw()
{
	if (m_pMap != nullptr)
	{
		m_pMap->draw();
	}
	if (m_pMap2 != nullptr)
	{
		m_pMap2->draw();
	}
	if (player->getPlayerLives() >= 0)
	{
		player->draw();
	}
	//if (m_pSpeedLabel != nullptr) {
	//	m_pSpeedLabel->draw();
	//}

	for (PlayerWeapon* pw : playerWeapons) {
		pw->draw();
	}
	for (AI* a : enemies) {
		if (!(a->GetParent()->getName() == "RespawningWall" && ((RespawningWallAI*)a)->isNotActive())) {
			a->GetParent()->draw();
		}
	}
	//if(m_pshield != nullptr)
	//{
	//	m_pshield->draw();
	//}
	if (!m_pExplosions.empty())
	{
		for (auto item : m_pExplosions)
		{
			item->draw();
		}
	}
	if (m_pLivesLabel != nullptr) {
		m_pLivesLabel->draw();
	}
	if (m_pScoreLabel != nullptr)
	{
		m_pScoreLabel->draw();
	}
	if (m_pHighScoreLabel != nullptr)
	{
		m_pHighScoreLabel->draw();
	}
}

void LevelScene::DestroyEnemy(Enemy* enemy)
{
	for (int i = 0; i < enemies.size(); ++i) {
		if (/*enemies[i]->GetParent().getPosition() == enemy->getPosition() && */enemies[i]->GetParent()->GetFrame()->getParent() == enemy) {
			//SpawnExplosion(enemies[i]->GetParent()->getPosition());
			enemies.erase(enemies.begin()+i);
			break;
		}
	}
}
void LevelScene::DestroyWeapon(PlayerWeapon* weapon)
{
	for (int i = 0; i < playerWeapons.size(); ++i) {
		if (playerWeapons[i]->getFrame()->getParent() == weapon) {
			playerWeapons.erase(playerWeapons.begin() + i);
			break;
		}
	}
}

void LevelScene::SpawnExplosion(glm::vec2 position)
{
	player->setKillCounter(1);
	m_pScoreLabel->setText("Score: " + std::to_string(Scoreboard::Instance()->getScore()));
	m_pHighScoreLabel->setText("HighScore: " + std::to_string(Scoreboard::Instance()->getHighScore()));
	idNum++;
	//std::cout << "Exp Num: "<< idNum << std::endl;
	expID = "exp " + std::to_string(idNum);
	Explosion* exp = new Explosion(expID);
	addChild(exp);
	exp->setPosition(position);
	m_pExplosions.push_back(exp);
	//DestroyExplosion();
}

PlayerShip* LevelScene::getPlayerShip()
{
	return player;
}

void LevelScene::addGarbage(std::string id)
{
	//std::cout << "Garbage is added: " << id << std::endl;
	garbage.push_back(id);
}

void LevelScene::collisionCheck(bool boss, AI* enemy, PlayerWeapon* pw)
{
	//Collision check for Enemies versus Player Weapon
	if (boss) {
		for (ShipComponent es : enemy->GetParent()->GetFrame()->GetBuild()) {
			if (es.getName() == "BasicBody") {
				for (ShipComponent ps : pw->getFrame()->GetBuild()) {
					if (ps.getName() == "IndesBody") {
						if (CollisionManager::shipComponentCheck(es, ps))
						{
							ShipComponent temp[2] = { ps, es };
							Damage(temp);
						}
					}
				}
			}
		}
	}
	else if (enemy->CircleCollider()) {
		if (CollisionManager::circleAABBCheck(enemy->GetParent(), pw) && enemy->GetParent()->getType() != ENEMY_WEAPON)
		{
			enemy->GetParent()->Damage(1);
			pw->Damage(1);
		}
	}
	else {
		if (CollisionManager::AABBCheck(enemy->GetParent(), pw) && enemy->GetParent()->getType() != ENEMY_WEAPON)
		{
			enemy->GetParent()->Damage(1);
			pw->Damage(1);
		}
	}
}

void LevelScene::collisionCheck(bool boss, AI* enemy)
{
	if (enemy->GetParent()->getName() == "RespawningWall" && ((RespawningWallAI*)enemy)->isNotActive()) {
		return;
	}
	//Collision Check used for enemies versus player
	if (boss)
	{
		for (ShipComponent es : enemy->GetParent()->GetFrame()->GetBuild()) {
			if (es.getName() == "BasicBody" || es.getName() == "IndesBody") {
				for (ShipComponent ps : player->GetFrame()->GetBuild()) {
					if (ps.getName() == "BasicBody") {
						if (CollisionManager::shipComponentCheck(es, ps))
						{
							ShipComponent temp[2] = { ps, es };
							Damage(temp);
							m_pLivesLabel->setText("Lives: " + std::to_string(player->getPlayerLives()));

						}
					}
				}
			}
		}
	}
	else {
		if (CollisionManager::AABBCheck(enemy->GetParent(), player))
		{
			if(!player->getInvincibility())
			{
				player->Damage(1);
				SpawnExplosion(player->getPosition());
				m_pLivesLabel->setText("Lives: " + std::to_string(player->getPlayerLives()));
			}
		}
	}
}

void LevelScene::Damage(ShipComponent sc[2])
{
	for (int z = 0; z < 2; ++z) {
		if (sc[z].getName() == "BasicBody") {
			int i = sc[1 - z].getParent()->getParent()->getName() == "Cannon" ? 2 : 1;
			((BasicBody&)sc[z]).Damage(i);
		}
		else if (sc[z].getName() == "IndesBody") {
			((IndesBody&)sc[z]).Damage(sc[1 - z]);
		}
	}
	//if (sc[0].getName() == "IndesBody" && sc[1].getName() == "BasicBody")
	//{
	//	if(!(((FlyOntoScreenAI*)((Enemy*)sc[1].getParent()->getParent())->getAI())->isBoss))
	//	{
	//		player->setKillCounter(1);
	//		player->addScore(1);//Temporary calling score method for testing.
	//		//player->addScore(/*some amount for score(integer)*/);
	//		m_pScoreLabel->setText("Score: " + std::to_string(Scoreboard::Instance()->getScore()));
	//		m_pHighScoreLabel->setText("HighScore: " + std::to_string(Scoreboard::Instance()->getHighScore()));
	//		
	//		
	//	}
	//	if (player->getKillCounter() > 0 &&
	//		player->getKillCounter() % 20 == 0)
	//	{
	//		spawnShield(sc);			
	//	}
	//}
}

void LevelScene::GameOver()
{
}

glm::vec2 LevelScene::getPlayerPosition()
{
	return ((GameObject*)player)->getPosition();
}

void LevelScene::spawnEnemy(AI* enemyAI)
{
	if (spawnedEnemy == false) {
		if (!enemyAI->GetParent()->getName().find("Wall") && !enemyAI->GetParent()->getName().find("Tetran")) {
			spawnedEnemy = true;
		}
		enemies.push_back(enemyAI);
	}
}

void LevelScene::spawnPlayerWeapon(PlayerWeapon* playerWeapon)
{
	playerWeapons.push_back(playerWeapon);
}

void LevelScene::initialize()
{
	if (player != nullptr && m_pLivesLabel == nullptr)
	{
		std::cout << "Initialized.\n";
		SDL_Color yellow = { 255, 255, 0, 255 };
		m_pLivesLabel = new Label("Lives: " + std::to_string(Scoreboard::Instance()->getLives()), "FSEX300",
			24, yellow, glm::vec2(Config::SCREEN_WIDTH * 0.75f, 10.0f), TTF_STYLE_NORMAL, true);
		/*m_pSpeedLabel = new Label("Speed: " + std::to_string(player->getPlayerSpeed()), "Consolas",
			24, yellow, glm::vec2(Config::SCREEN_WIDTH * 0.65f, 10.0f), TTF_STYLE_NORMAL, false);*/
		m_pScoreLabel = new Label("Score: " + std::to_string(Scoreboard::Instance()->getScore()), "FSEX300",
			24, yellow, glm::vec2(Config::SCREEN_WIDTH * 0.25f, 10.0f), TTF_STYLE_NORMAL,true);
		m_pHighScoreLabel = new Label("HighScore: " + std::to_string(Scoreboard::Instance()->getHighScore()), "FSEX300",
			24, yellow, glm::vec2(Config::SCREEN_WIDTH * 0.5f, 10.0f), TTF_STYLE_NORMAL, true);

		
		
		
		return;
	}
}

void LevelScene::removeGarbage()
{
	if(!garbage.empty())
	{
		for (auto item : garbage)
		{
			for (int i = 0; i < m_pExplosions.size(); i++)
			{
				if (item == m_pExplosions[i]->getID())
				{
					//std::cout << "Removing garbage: " << m_pExplosions[i] << std::endl;
					m_pExplosions.erase(m_pExplosions.begin() + i);
					break;
				}
			}
		}
		//std::cout << "All garbage is cleared\n";
		garbage.clear();
		garbage.shrink_to_fit();
	}
}


