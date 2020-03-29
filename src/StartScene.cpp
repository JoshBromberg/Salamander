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
	m_pStartLabel->draw();
	m_pGuildLabel->draw();
	m_pStartButton->draw();
	m_pLevel2Button->draw();
	m_pLevel3Button->draw();
	m_pGuild1_Button->draw();
	m_pGuild2_Button->draw();
}

void StartScene::update()
{
	m_pStartButton->setMousePosition(m_mousePosition);
	m_pLevel2Button->setMousePosition(m_mousePosition);
	m_pLevel3Button->setMousePosition(m_mousePosition);
	m_pGuild1_Button->setMousePosition(m_mousePosition);
	m_pGuild2_Button->setMousePosition(m_mousePosition);
	
	if(m_pStartButton->ButtonClick())
	{
		if(Game::Instance()->getGuild() == 0)
		{
			m_pGuildLabel->setText("Guild: You have to choose a guild");
		}
		else
		{
			TheGame::Instance()->changeSceneState(LEVEL1_SCENE);
		}
	}
	if (m_pLevel2Button->ButtonClick())
	{
		if (Game::Instance()->getGuild() == 0)
		{
			m_pGuildLabel->setText("Guild: You have to choose a guild");
		}
		else
		{
			TheGame::Instance()->changeSceneState(LEVEL2_SCENE);
		}
	}
	if(m_pLevel3Button->ButtonClick())
	{
		if (Game::Instance()->getGuild() == 0)
		{
			m_pGuildLabel->setText("Guild: You have to choose a guild");
		}
		else
		{
			TheGame::Instance()->changeSceneState(LEVEL3_SCENE);
		}
	}
	if(m_pGuild1_Button->ButtonClick())
	{
		m_pGuildLabel->setText("Guild: Guild1");
		TheGame::Instance()->setGuild(1);
	}
	if (m_pGuild2_Button->ButtonClick())
	{
		m_pGuildLabel->setText("Guild: Guild2");
		TheGame::Instance()->setGuild(2);
	}
}

void StartScene::clean()
{
	delete m_pStart_Scene_Bg;
	delete m_pStartButton;
	delete m_pStartLabel;
	delete m_pGuildLabel;
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
				m_pLevel2Button->setMouseButtonClicked(true);
				m_pLevel3Button->setMouseButtonClicked(true);
				m_pGuild1_Button->setMouseButtonClicked(true);
				m_pGuild2_Button->setMouseButtonClicked(true);
				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pStartButton->setMouseButtonClicked(false);
				m_pLevel2Button->setMouseButtonClicked(false);
				m_pLevel3Button->setMouseButtonClicked(false);
				m_pGuild1_Button->setMouseButtonClicked(false);
				m_pGuild2_Button->setMouseButtonClicked(false);
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
			case SDLK_1:
				TheGame::Instance()->changeSceneState(SceneState::LEVEL1_SCENE);
				//TheGame::Instance()->changeSceneState(SceneState::LEVEL3_SCENE);
				break;
			case SDLK_2:
				TheGame::Instance()->changeSceneState(END_SCENE);
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
	
	SDL_Color black = { 0, 0, 0, 255 };
	m_pStartLabel = new Label("Guild of Agnis", "Dock51",
		80, black, glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.2f));
	addChild(m_pStartLabel);

	m_pGuildLabel = new Label("Guild: ", "Dock51",
		40, black, glm::vec2(Config::SCREEN_WIDTH * 0.25f, Config::SCREEN_HEIGHT * 0.6f),
		false,false);
	addChild(m_pGuildLabel);
	
	m_pStartButton = new StartButton();
	addChild(m_pStartButton);
	playSound("Menu", 999);

	m_pLevel2Button = new Level2Button();
	addChild(m_pLevel2Button);
	
	m_pLevel3Button = new Level3Button();
	addChild(m_pLevel3Button);

	m_pGuild1_Button = new Guild1_Button();
	addChild(m_pGuild1_Button);
	m_pGuild2_Button = new Guild2_Button();
	addChild(m_pGuild2_Button);

}

void StartScene::loadAllSounds()
{
	std::cout << "Loading sounds" << std::endl;
	loadSound("../Assets/audio/menu.ogg", "Menu", SOUND_MUSIC);
	std::cout << "Finished loading sounds" << std::endl;
}

void StartScene::loadAllTextures()
{
	std::cout << "Loading Textures" << std::endl;
	loadTexture("../Assets/textures/StartSceneBg.png", "Start_Scene_Bg");
	loadTexture("../Assets/textures/Level1.png", "Level1Button");
	loadTexture("../Assets/textures/Level2.png", "Level2Button");
	loadTexture("../Assets/textures/Level3.png", "Level3Button");
	loadTexture("../Assets/textures/guild1_Button.png", "guild1_Button");
	loadTexture("../Assets/textures/guild2_Button.png", "guild2_Button");
	std::cout << "Finish loading textures" << std::endl;
}