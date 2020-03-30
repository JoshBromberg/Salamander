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

	};
	fanSpawnLocation = {

	};

	
	player = new PlayerShip(1, 5, glm::vec2(100, Config::SCREEN_HEIGHT / 2));
	m_pMap = new Map();
	m_pMap2 = new Map();
	m_pMap->setPosition(glm::vec2(0, 0));
	m_pMap2->setPosition(glm::vec2(1950, 0));
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
	//load the texture with loadTexture() with params path and id respectively
	if(Game::Instance()->getGuild() == 1)
	{
		loadTexture("../Assets/textures/player1.png", "Player");
	}
	else
	{
		loadTexture("../Assets/textures/player2.png", "Player");
	}
	loadTexture("../Assets/textures/background.png", "map");
	loadTexture("../Assets/textures/Fan.png", "Fan");
}

void Level1::loadAllSounds()
{
	loadSound("../Assets/audio/LevelMusicStart.ogg", "Level1", SOUND_MUSIC);
	loadSound("../Assets/audio/LevelMusicLoop.ogg", "Level1Loop", SOUND_MUSIC);
}
