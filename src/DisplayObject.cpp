#include "DisplayObject.h"
#include "Game.h"

Scene * DisplayObject::getParent()
{
	return m_pParentScene;
}

void DisplayObject::setParent(Scene * parent)
{
	m_pParentScene = parent;
}

//Change Texture:
//this changes the texture for the current object by using the id and sets the texture size
void DisplayObject::changeTexture(std::string idName)
{
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize(idName);
	if(size.x == -1 || size.y == -1)
	{
		std::cout << "unable to get texture for id name:" << idName << std::endl;
	}
	else
	{
		std::cout << "Texture found for id name: " << idName << std::endl;
		name = idName;
		setWidth(size.x);
		setHeight(size.y);
	}
}

void DisplayObject::Damage(int i) //Do not use!
{
	if (name == "Cannonball") {
		TheGame::Instance()->destroyWeapon((PlayerWeapon*)this);
	}
}