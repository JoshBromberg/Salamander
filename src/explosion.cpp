#include "explosion.h"
#include "Game.h"

Explosion::Explosion(std::string id):m_currentFrame(0),m_currentRow(0),animated(false)
{
	ID = id;
	TheTextureManager::Instance()->load("../Assets/textures/explosion.png",
		ID, TheGame::Instance()->getRenderer());

	auto size = TheTextureManager::Instance()->getTextureSize(ID);
	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(400.0f, 300.0f));
	setIsColliding(false);
	setType(EXPLOSION);
}
Explosion::~Explosion()
{
	delete this;
}
void Explosion::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;
	
	TheTextureManager::Instance()->drawFrame(ID, xComponent,
	yComponent, 64, 64, m_currentRow,
	m_currentFrame, TheGame::Instance()->getRenderer(),
	4, 4, 1.0f,
	TheGame::Instance()->getRenderer(), 180, 255, true);
}

void Explosion::update()
{
}

void Explosion::clean()
{

}

std::string Explosion::getID()
{
	return ID;
}
