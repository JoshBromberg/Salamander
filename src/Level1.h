#pragma once
#ifndef  __LEVEL1__
#define  __LEVEL1__
#include "LevelScene.h"

class Level1 : public LevelScene
{
public:

	Level1();
	~Level1();

	void clean() override;
	void handleEvents() override;
	void start() override;
	void loadAllTextures();
	void loadAllSounds();
private:
	glm::vec2 c = { 1380, 360 };
	int d = 160;
};
#endif /* defined __LEVEL1__ */