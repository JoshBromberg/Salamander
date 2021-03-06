#pragma once
#ifndef __LEVELSCENE__
#define __LEVELSCENE__

#include "PlayerShip.h"
#include "AI.h"
#include "Map.h"
#include "Label.h"
#include <SDL_ttf.h>
#include "Control_Img.h"
#include "explosion.h"
#include "PlayerWeapon.h"

class LevelScene : public Scene
{
public:
	LevelScene();
	virtual ~LevelScene();
	void update() override;
	void draw() override;
	void DestroyEnemy(Enemy* enemy);
	void DestroyWeapon(PlayerWeapon* weapon);
	void SpawnExplosion(glm::vec2 position);
	void GameOver();
	glm::vec2 getPlayerPosition();
	void spawnEnemy(AI* enemyAI);
	void spawnPlayerWeapon(PlayerWeapon* playerWeapon);
	PlayerShip* getPlayerShip();

	void addGarbage(std::string id);
protected:
	bool scrolling = true, spawnedEnemy=false;
	#pragma region Game Objects
	std::vector<AI*> enemies;
	PlayerShip* player;
	SDL_Color yellow = { 255, 255, 0, 255 };
	//Label* m_pSpeedLabel;
	Label* m_pLivesLabel;
	Label* m_pScoreLabel;
	Label* m_pHighScoreLabel;

	std::vector<PlayerWeapon*> playerWeapons;
	glm::vec2 shieldSpawnPos;
	std::vector<Explosion*> m_pExplosions;

	Map* m_pMap;
	Map* m_pMap2;
	#pragma endregion
	#pragma region Spawn Timers
	int time = 0, fanIteration = 0, deathHandIteration = 0, octaIteration = 0, sharpCrossIteration = 0, sparugIteration = 0, respawningWallIteration = 0;
	std::vector<int> fanSpawnTimer, deathHandSpawnTimer, octaSpawnTimer, sharpCrossSpawnTimer, sparugSpawnTimer, respawningWallTimer;
	std::vector<glm::vec2> fanSpawnLocation, deathHandSpawnLocation, octaSpawnLocation, sharpCrossSpawnLocation, sparugSpawnLocation, respawningWallSpawnLocation;
	#pragma endregion

	int level;
private:
	bool bossActive = false;
	void Damage(ShipComponent sc[2]);
	void collisionCheck(bool boss, AI* enemy, PlayerWeapon* pw);
	void collisionCheck(bool boss, AI* enemy);
	void initialize();
	void removeGarbage();
	int idNum = 0;
	std::string shieldID;
	std::string expID;
	std::vector<std::string> garbage;
};
#endif