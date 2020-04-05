#pragma once
#include "PlayerShip.h"
#include "Game.h"
#include <iostream>
#include "Frame.h"
#include "LevelScene.h"
#include "BasicBody.h"
#include "MissileLauncher.h"
#include "Blank.h"
#include "CannonBall.h"
#include <functional>
#include <glm/detail/type_vec2.hpp>
#include "Scoreboard.h"

PlayerShip::PlayerShip(int health, int lives, glm::vec2 targetTransform)
:m_isMoving(false), m_maxSpeed(9.0f), m_alpha(255),name("Player"),inv(false),killCounter(0),shieldAvailable(false)
{
	changeTexture("Player");
	setPosition(targetTransform);
	setIsColliding(false);
	setType(GameObjectType::PLAYER);

	std::vector<ShipComponent> build =
#pragma region Frame Construction
	{
		BasicBody()
	};
#pragma endregion
	frame = new Frame(1,
		build, 1, 1);
	frame->Initialize(this);
	playerLives = 9;
	playerHealth = health;
}

PlayerShip::~PlayerShip()
{
	
}

void PlayerShip::Damage(int i)
{
	if (playerHealth >= 1 && playerLives >= 0 && !inv)
	{
		std::cout << "Player damaged!\n";
		std::cout << "PlayerHealth: " << playerHealth << std::endl;
		if(shieldAvailable && playerLives == 0)
		{
			invincible();
			std::cout << "Used shield!\n";
			shieldAvailable = false;
		}
		playerLives -= 1;
		std::cout << "Player life decreases for 1!" << std::endl;
		//playerHealth += 1;
		std::cout << "Player life restored by a decreased life: " << playerHealth << std::endl;
			invincible();
		}
		else
		{
			std::cout << "Player damaged!\n";
			playerHealth -= 1;
			std::cout << "PlayerHealth: " << playerHealth << std::endl;
			playerLives -= 1;
			std::cout << "Player life decreases for 1!" << std::endl;
			playerHealth += 1;
			std::cout << "Player life restored by a decreased life: " << playerHealth << std::endl;
			invincible();
		}
}
bool PlayerShip::getInvincibility()
{
	return inv;
}

void PlayerShip::invincible()
{
	//if not invincible do this
	if (!inv)
	{
		std::cout << "Invincibled!\n";
		inv = true;
		m_alpha *= 0.5f;
		endInvincibleTime = SDL_GetTicks() + 3000; // 3 seconds
	}
}

void PlayerShip::checkBound()
{
	if(getPosition().x <= Config::SCREEN_WIDTH * 0.03f)
	{
		setPosition(glm::vec2(Config::SCREEN_WIDTH * 0.03f, getPosition().y));
	}
	if (getPosition().x >= Config::SCREEN_WIDTH * 0.97f)
	{
		setPosition(glm::vec2(Config::SCREEN_WIDTH * 0.97f, getPosition().y));
	}
	if(getPosition().y <= Config::SCREEN_HEIGHT * 0.03f)
	{
		setPosition(glm::vec2(getPosition().x, Config::SCREEN_HEIGHT * 0.03f));
	}
	if (getPosition().y >= Config::SCREEN_HEIGHT * 0.97f)
	{
		setPosition(glm::vec2(getPosition().x, Config::SCREEN_HEIGHT * 0.97f));
	}
}

int PlayerShip::getKillCounter()
{
	return killCounter;
}

void PlayerShip::setKillCounter(int num)
{
		killCounter += num;
		std::cout << killCounter << std::endl;
}

bool PlayerShip::getShieldAvailable()
{
	return shieldAvailable;
}

void PlayerShip::setShieldAvailable(bool newState)
{
	shieldAvailable = newState;
}

void PlayerShip::initializeKillCounter()
{
	killCounter = 0;
}

void PlayerShip::Fire()
{
	TheGame::Instance()->spawnPlayerWeapon(new Cannonball(glm::vec2(getPosition().x+25, getPosition().y), glm::vec2(15, 0)));
}

Frame* PlayerShip::GetFrame()
{
	return frame;
}
void PlayerShip::draw()
{
	TheTextureManager::Instance()->draw
	("Player", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(),0,m_alpha, true);
}

void PlayerShip::move(Move newMove)
{
		switch (newMove)
		{
		case RIGHT:
			setVelocity(glm::vec2(1.0f * m_maxSpeed, getVelocity().y));
			break;
		case LEFT:
			setVelocity(glm::vec2(-1.0f * m_maxSpeed, getVelocity().y));
			break;
		case UP:
			setVelocity(glm::vec2(getVelocity().x, -1.0f * m_maxSpeed));
			break;
		case DOWN:
			setVelocity(glm::vec2(getVelocity().x, 1.0f * m_maxSpeed));
			break;
		}
}

bool PlayerShip::getIsMoving()
{
	return m_isMoving;
}

void PlayerShip::setIsMoving(bool newState)
{
	m_isMoving = newState;
}

int PlayerShip::getPlayerLives()
{
	return playerLives;
}

void PlayerShip::setPlayerLives(int num)
{
	playerLives += num;
	Scoreboard::Instance()->setLives(playerLives);
}

int PlayerShip::getScore()
{
	return playerScore;
}

void PlayerShip::addScore(int num)
{
	playerScore += num;
	Scoreboard::Instance()->setScore(playerScore);
}

float PlayerShip::getPlayerSpeed()
{
	return m_maxSpeed;
}

void PlayerShip::setPlayerSpeed(float num)
{
	m_maxSpeed = num;
}

void PlayerShip::update()
{
	auto currentPosition = getPosition();
	auto currentVelocity = getVelocity();

	//if (m_isMoving == false)
	//{
	//	currentVelocity.x *= 0.9f;
	//	currentVelocity.y *= 0.9f;
	//}
	if (playerLives >= 0)
	{
		setVelocity(glm::vec2(currentVelocity.x, currentVelocity.y));
		auto deltax = currentPosition.x + currentVelocity.x;
		auto deltay = currentPosition.y + currentVelocity.y;
		setPosition(glm::vec2(deltax, deltay));
	}
	
	//when the invincibility has finished run this
	if (inv == true && endInvincibleTime <= SDL_GetTicks())
	{
		std::cout << "invincible finished!\n";
		inv = false;
		m_alpha = defaultAlpha;
	}
	checkBound();
}

void PlayerShip::clean()
{
}


