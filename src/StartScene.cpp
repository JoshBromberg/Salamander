#include "StartScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include <iomanip>

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
{
}

void StartScene::draw()
{
	m_pStart_Scene_Bg->draw();
	m_pStartButton->draw();
	m_pInstructionsButton->draw();
	m_pExitButton->draw();
	m_pLoadButton->draw();
}

void StartScene::update()
{
	m_pStartButton->setMousePosition(m_mousePosition);
	m_pInstructionsButton->setMousePosition(m_mousePosition);
	m_pExitButton->setMousePosition(m_mousePosition);
	m_pLoadButton->setMousePosition(m_mousePosition);
	
	if(m_pStartButton->ButtonClick())
	{
		TheGame::Instance()->changeSceneState(LEVEL1_SCENE);
	}
	else if(m_pInstructionsButton->ButtonClick() && !instructions)
	{
		instructions = true;
	}
	else if(m_pExitButton->ButtonClick())
	{
		exit(0);
	}
	else if(m_pLoadButton->ButtonClick())
	{
		//Load();
	}
}

void StartScene::clean()
{
	delete m_pStart_Scene_Bg;
	delete m_pStartButton;
	delete m_pInstructionsButton;
	delete m_pExitButton;
	delete m_pLoadButton;
	removeAllChildren();
}

void StartScene::handleEvents()
{
	SDL_Event event;
	int wheel = 0;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pStartButton->setMouseButtonClicked(true);
				m_pInstructionsButton->setMouseButtonClicked(true);
				m_pExitButton->setMouseButtonClicked(true);
				m_pLoadButton->setMouseButtonClicked(true);
				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pStartButton->setMouseButtonClicked(false);
				m_pInstructionsButton->setMouseButtonClicked(false);
				m_pExitButton->setMouseButtonClicked(false);
				m_pLoadButton->setMouseButtonClicked(false);
				break;
			}
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			}
			break;

		default:
			break;
		}
	}
}

void StartScene::start()
{
	loadAllTextures();
	loadAllSounds();
	m_pStart_Scene_Bg = new Start_Scene_Bg();
	addChild(m_pStart_Scene_Bg);
	
	m_pStartButton = new Button(
		"PlayButton",
		PLAY_BUTTON, glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.75f));
	addChild(m_pStartButton);
	//playSound("Menu", 999);
	
	m_pInstructionsButton = new Button(
		"InstructionsButton",
		INSTRUCTIONS_BUTTON, glm::vec2(Config::SCREEN_WIDTH * 0.7f, Config::SCREEN_HEIGHT * 0.75f));
	addChild(m_pInstructionsButton);
	
	m_pExitButton = new Button("ExitButton",
		EXIT_BUTTON, glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.9f));
	addChild(m_pExitButton);

	m_pLoadButton = new Button("LoadButton",
		LOAD_BUTTON, glm::vec2(Config::SCREEN_WIDTH * 0.3f, Config::SCREEN_HEIGHT * 0.75f));
	addChild(m_pLoadButton);
	

}

void StartScene::loadAllSounds()
{
	std::cout << "Loading sounds" << std::endl;
	//loadSound("../Assets/audio/menu.ogg", "Menu", SOUND_MUSIC);
	std::cout << "Finished loading sounds" << std::endl;
}

void StartScene::loadAllTextures()
{
	std::cout << "Loading Textures" << std::endl;
	loadTexture("../Assets/textures/Menu.png", "Start_Scene_Bg");
	loadTexture("../Assets/textures/Play.png", "PlayButton");
	loadTexture("../Assets/textures/Instructions.png", "InstructionsButton");
	loadTexture("../Assets/textures/Exit.png", "ExitButton");
	loadTexture("../Assets/textures/LoadGame.png", "LoadButton");
	std::cout << "Finish loading textures" << std::endl;
}
