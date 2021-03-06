#include "Level1.h"
#include "Map.h"
#include "Config.h"
#include "Game.h"


Level1::Level1()
{
	level = 1;
	loadAllTextures();
	loadAllSounds();
	
	fanSpawnTimer = {
		180, 190, 200, 210, 220,
		300, 310, 320, 330, 340,
		420, 430, 440, 450, 460,
		540, 550, 560, 570, 580,
		660, 670, 680, 690, 700,
		780, 790, 800, 810, 820,
		900, 910, 920, 930, 940,
		1020, 1030, 1040, 1050, 1060,
		1140, 1150, 1160, 1170, 1180,
		1260, 1270, 1280, 1290, 1300
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
	deathHandSpawnTimer = {
		
		1860, //top
		2880, //bot
		2940, //top
		3240, //bot
		3241, //top
		4380, //bot
		5936, //bot mid
		5968 //top mid
	};
	deathHandSpawnLocation = {
		{Config::SCREEN_WIDTH + 20, -d},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT + d},
		{Config::SCREEN_WIDTH + 20, -d},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT + d},
		{Config::SCREEN_WIDTH + 20, -d},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT + d},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT / 2 + d * 2},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT / 2 - d * 2}
	};
	octaSpawnTimer = {
		2400,
		2820,
		3120,
		3121,
		3360,
		3361,
		5640,
		5641,
		6360,
		6361
	};
	octaSpawnLocation = {
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT - Config::SCREEN_HEIGHT / 3}, //bot mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT / 3}, //top mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT - Config::SCREEN_HEIGHT / 3}, //bot mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT / 3}, //top mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT - Config::SCREEN_HEIGHT / 3}, //bot mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT / 3}, //top mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT - Config::SCREEN_HEIGHT / 3}, //bot mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT / 3}, //top mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT - Config::SCREEN_HEIGHT / 3}, //bot mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT / 3}, //top mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT - Config::SCREEN_HEIGHT / 3}, //bot mid
		{Config::SCREEN_WIDTH + 40, Config::SCREEN_HEIGHT / 3} //top mid
	};
	sharpCrossSpawnTimer = {
		4860,
		4920,
		4980, //top
		5040, //bot
		5100, //top
		5101, //bot
		5160, //bot
		5220 //top
	};
	sharpCrossSpawnLocation = {
		{Config::SCREEN_WIDTH + 48, -144},
		{Config::SCREEN_WIDTH + 48, Config::SCREEN_HEIGHT + 144},
		{Config::SCREEN_WIDTH + 48, -144},
		{Config::SCREEN_WIDTH + 48, Config::SCREEN_HEIGHT + 144},
		{Config::SCREEN_WIDTH + 48, -144},
		{Config::SCREEN_WIDTH + 48, Config::SCREEN_HEIGHT + 144},
		{Config::SCREEN_WIDTH + 48, Config::SCREEN_HEIGHT + 144},
		{Config::SCREEN_WIDTH + 48, -144}
	};
	sparugSpawnTimer = {
		2040,
		2041,
		3900, 
		3901, 
		3960, 
		3961, 
		6040, //top
		6041, //bottom
		6060, //top
		6061, //bottom
		6080, //top
		6081, //bottom
		6300, //top
		6301, //bottom
		6320, //top
		6321, //bottom
	};
	sparugSpawnLocation = {
		{Config::SCREEN_WIDTH + 20, 50},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT - 50},
		{Config::SCREEN_WIDTH + 20, 50},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT - 50},
		{Config::SCREEN_WIDTH + 20, 50},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT - 50},
		{Config::SCREEN_WIDTH + 20, 50},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT - 50},
		{Config::SCREEN_WIDTH + 20, 50},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT - 50},
		{Config::SCREEN_WIDTH + 20, 50},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT - 50},
		{Config::SCREEN_WIDTH + 20, 50},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT - 50},
		{Config::SCREEN_WIDTH + 20, 50},
		{Config::SCREEN_WIDTH + 20, Config::SCREEN_HEIGHT - 50},
	};
	respawningWallTimer = {
		5890, 5891, 5892, 5893, 5894, 5895, 5896, 5897, 5898, 5899,
		5900, 5901, 5902, 5903, 5904, 5905, 5906, 5907, 5908, 5909,
		5910, 5911, 5912, 5913, 5914, 5915, 5916, 5917, 5918, 5919,
		5920, 5921, 5922, 5923, 5924, 5925, 5926, 5927, 5928, 5929,
		5930, 5931, 5932, 5933, 5934, 5935, 5936, 5937, 5938, 5939
	};
	respawningWallSpawnLocation = {
		{Config::SCREEN_WIDTH + 250, 20},{Config::SCREEN_WIDTH + 245, 60},{Config::SCREEN_WIDTH + 240, 100},{Config::SCREEN_WIDTH + 235, 140},{Config::SCREEN_WIDTH + 230, 180},
		{Config::SCREEN_WIDTH + 225, Config::SCREEN_HEIGHT - 20},{Config::SCREEN_WIDTH + 220, Config::SCREEN_HEIGHT - 60},{Config::SCREEN_WIDTH + 215, Config::SCREEN_HEIGHT - 100},{Config::SCREEN_WIDTH + 210, Config::SCREEN_HEIGHT - 140},{Config::SCREEN_WIDTH + 205, Config::SCREEN_HEIGHT - 180},
		{Config::SCREEN_WIDTH + 240, 20},{Config::SCREEN_WIDTH + 235, 60},{Config::SCREEN_WIDTH + 230, 100},{Config::SCREEN_WIDTH + 225, 140},{Config::SCREEN_WIDTH + 220, 180},
		{Config::SCREEN_WIDTH + 215, Config::SCREEN_HEIGHT - 20},{Config::SCREEN_WIDTH + 210, Config::SCREEN_HEIGHT - 60},{Config::SCREEN_WIDTH + 205, Config::SCREEN_HEIGHT - 100},{Config::SCREEN_WIDTH + 200, Config::SCREEN_HEIGHT - 140},{Config::SCREEN_WIDTH + 195, Config::SCREEN_HEIGHT - 180},
		{Config::SCREEN_WIDTH + 230, 20},{Config::SCREEN_WIDTH + 225, 60},{Config::SCREEN_WIDTH + 220, 100},{Config::SCREEN_WIDTH + 215, 140},{Config::SCREEN_WIDTH + 210, 180},
		{Config::SCREEN_WIDTH + 205, Config::SCREEN_HEIGHT - 20},{Config::SCREEN_WIDTH + 200, Config::SCREEN_HEIGHT - 60},{Config::SCREEN_WIDTH + 195, Config::SCREEN_HEIGHT - 100},{Config::SCREEN_WIDTH + 190, Config::SCREEN_HEIGHT - 140},{Config::SCREEN_WIDTH + 185, Config::SCREEN_HEIGHT - 180},
		{Config::SCREEN_WIDTH + 220, 20},{Config::SCREEN_WIDTH + 215, 60},{Config::SCREEN_WIDTH + 210, 100},{Config::SCREEN_WIDTH + 205, 140},{Config::SCREEN_WIDTH + 200, 180},
		{Config::SCREEN_WIDTH + 195, Config::SCREEN_HEIGHT - 20},{Config::SCREEN_WIDTH + 190, Config::SCREEN_HEIGHT - 60},{Config::SCREEN_WIDTH + 185, Config::SCREEN_HEIGHT - 100},{Config::SCREEN_WIDTH + 180, Config::SCREEN_HEIGHT - 140},{Config::SCREEN_WIDTH + 175, Config::SCREEN_HEIGHT - 180},
		{Config::SCREEN_WIDTH + 210, 20},{Config::SCREEN_WIDTH + 205, 60},{Config::SCREEN_WIDTH + 200, 100},{Config::SCREEN_WIDTH + 195, 140},{Config::SCREEN_WIDTH + 190, 180},
		{Config::SCREEN_WIDTH + 190, Config::SCREEN_HEIGHT - 20},{Config::SCREEN_WIDTH + 180, Config::SCREEN_HEIGHT - 60},{Config::SCREEN_WIDTH + 175, Config::SCREEN_HEIGHT - 100},{Config::SCREEN_WIDTH + 170, Config::SCREEN_HEIGHT - 140},{Config::SCREEN_WIDTH + 165, Config::SCREEN_HEIGHT - 180},
	};
	for (int i = 270, j = 0, k = 5972; j < 7; ++j, i += 5) {
		for (int z = 0;z < 7;++z, ++k) {
			respawningWallSpawnLocation.push_back({ Config::SCREEN_WIDTH + i - z * 5, (Config::SCREEN_HEIGHT / 2 - 100) + (z * 40) });
			respawningWallTimer.push_back(k);
		}
	}
	for (int i = 600, j = 0, k = 6021; j < 12; ++j, i -= 50) {
		for (int z = 0;z < 18;++z, ++k) {
			respawningWallSpawnLocation.push_back({ Config::SCREEN_WIDTH + i - (z * 5), 20 + (z * 40) });
			respawningWallTimer.push_back(k);
		}
	}
	for (int i = 1100, j = 0, k = 6238; j < 22; ++j, i -= 50) {
		for (int z = 0;z < 18;++z, ++k) {
			respawningWallSpawnLocation.push_back({ Config::SCREEN_WIDTH + i - (z * 5), 20 + (z * 40) });
			respawningWallTimer.push_back(k);
		}
	}

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
	loadTexture("../Assets/textures/DeathHand.png", "DeathHand");
	loadTexture("../Assets/textures/Octa.png", "Octa");
	loadTexture("../Assets/textures/SharpCross.png", "SharpCross");
	loadTexture("../Assets/textures/SharpCross2.png", "SharpCross2");
	loadTexture("../Assets/textures/Sparug.png", "Sparug");
	loadTexture("../Assets/textures/EnemyMissile.png", "EnemyMissile");
	loadTexture("../Assets/textures/RespawningWall.png", "RespawningWall");
	loadTexture("../Assets/textures/Wall.png", "Wall");
	loadTexture("../Assets/textures/Tetran.png", "Tetran");
	loadTexture("../Assets/textures/TetranShield.png", "TetranShield");
	loadTexture("../Assets/textures/TetranArm.png", "TetranArm");
	loadTexture("../Assets/textures/Cannonball.png", "Cannonball");
	loadTexture("../Assets/textures/explosion.png", "Explosion");
}

void Level1::loadAllSounds()
{
	loadSound("../Assets/audio/LevelMusicStart.ogg", "Level1", SOUND_MUSIC);
	loadSound("../Assets/audio/LevelMusicLoop.ogg", "Level1Loop", SOUND_MUSIC);
	loadSound("../Assets/audio/BossMusic.ogg", "Boss", SOUND_MUSIC);
}
