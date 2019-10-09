#ifndef APPLICATION
#define APPLICATION

#include <SFML/Graphics.hpp>
#include "GameMenu.h"
#include "GameWorld.h"
#include "ShipSelect.h"
#include "GameOver.h"
#include "HowToPlay.h"
#include "HUD.h"
#include "PauseMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static int			selection;

class Application :
	public sf::NonCopyable
{
public:
	Application(int windowWidth, int windowHeight);
	~Application();

	void			run();

private:
	void				update(sf::Time& elapsedTime);
	void				render();

	bool				m_initialised;
	bool				m_previousDownKeyPressed;
	bool				m_previousUpKeyPressed;
	bool				m_previousSpaceBarPressed;

	enum AppState
	{
		MAINMENU,
		SHIPMENU,
		GAMEPLAYING,
		EXITING,
		GAMEOVERSCREEN,
		HOWTOPLAYSCREEN,
		PAUSESCREEN,
	};

	enum ShipSelection
	{
		GNAT,
		MANTIS,
		TUG,
	};

	AppState			m_appState;
	ShipSelection		m_shipSelection;

	sf::RenderWindow	m_window;
	std::size_t			m_screenWidth;
	std::size_t			m_screenHeight;

	sf::Event			m_event;
	sf::Font			m_textFont;
	sf::Text			m_messageText;

	GameMenu			m_mainMenu;
	GameWorld			m_gameWorld;
	ShipSelect			m_shipSelect;
	GameOver			m_gameOverScreen;
	HowToPlay			m_howToPlayScreen;
	PauseMenu			m_pauseMenu;

	sf::Time			m_timeCounter;
	sf::Time			m_desiredUpdateTime;
	std::size_t			m_FPSCounter;
};
#endif