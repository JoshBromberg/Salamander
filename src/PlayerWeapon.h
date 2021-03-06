#pragma once
#ifndef __PLAYERWEAPON__
#define __PLAYERWEAPON__
#include "DisplayObject.h"
#include "Frame.h"
class PlayerWeapon : public DisplayObject
{
public:
	PlayerWeapon();
	~PlayerWeapon();
	void start();
	void draw() override;
	void update() override;
	void clean() override;

	void Move();
	Frame* getFrame();
protected:
	glm::vec2 speed;
	Frame* frame;

};
#endif // !__PLAYERWEAPON__
