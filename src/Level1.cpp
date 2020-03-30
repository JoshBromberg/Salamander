#include "Level1.h"
#include "Map.h"
#include "Config.h"
#include "RainAI.h"
#include "Game.h"


Level1::Level1()
{
	level = 1;
	loadAllTextures();
	loadAllSounds();
	
	fanSpawnTimer = {
		180, 195, 210, 225, 240,
		300, 315, 330, 345, 360,
		420, 435, 450, 465, 480,
		540, 555, 570, 585, 600,
		660, 675, 690, 705, 720,
		780, 795, 810, 825, 840,
		900, 915, 930, 945, 960,
		1020, 1035, 1050, 1065, 1080,
		1140, 1155, 1170, 1185, 1200,
		1260, 1275, 1290, 1305, 1320
	};
	fanSpawnLocation = {
		c, c, c, c, c,
		c, c, c, c, c,
		c, c, c, c, c,
		c, c, c, c, c,
		c, c, c, c, c,
		c, c, c, c, c,
		c, c, c, c, c,
		c, c, c, c, c,
		c, c, c, c, c,
		c, c, c, c, c
	};

	
	player = new PlayerShip(1, 5, glm::vec2(100, Config::SCREEN_HEIGHT / 2));
	m_pMap = new Map();
	m_pMap2 = new Map();
	m_pMap->setPosition(glm::vec2(0, 0));
	m_pMap2->setPosition(glm::vec2(1280, 0));
	//m_pSpeedLabel = new Label("Speed: ", "Consolas",
	//	24, yellow, glm::vec2(Config::SCREEN_WIDTH * 0.45f, 10.0f), TTF_STYLE_NORMAL, false);
	playSound("Level1", 1);
	//m_pLivesLabel = new Label("Lives: ", "Consolas",
	//	24, yellow, glm::vec2(Config::SCREEN_WIDTH * 0.65f, 10.0f), TTF_STYLE_NORMAL, false);
	std::cout << "guild num: " << Game::Instance()->getGuild() << std::endl;
}

Level1::~Level1()
{
}

void Level1::clean()
{
	delete player;
	delete m_pMap;
	delete m_pMap2;
	removeAllChildren();
}

void Level1::handleEvents()
{
	if (time == 640) {
		playSound("Level1Loop", 999);
	}
}

void Level1::start()
{
	
}
void Level1::loadAllTextures()
{
	loadTexture("../Assets/textures/Player.png", "Player");
	loadTexture("../Assets/textures/Background.png", "map");
	loadTexture("../Assets/textures/Fan.png", "Fan");
}

void Level1::loadAllSounds()
{
	loadSound("../Assets/audio/LevelMusicStart.ogg", "Level1", SOUND_MUSIC);
	loadSound("../Assets/audio/LevelMusicLoop.ogg", "Level1Loop", SOUND_MUSIC);
}
