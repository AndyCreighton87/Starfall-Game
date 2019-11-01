#include "Application.h"

Application::Application(int windowWidth, int windowHeight)
	: m_window(sf::VideoMode(windowWidth, windowHeight), "STARFALL")
	, m_initialised(true)
	, m_screenWidth(windowWidth)
	, m_screenHeight(windowHeight)
	, m_appState(MAINMENU)
	, m_mainMenu("Media/MenuInfo/mainmenu.txt", windowWidth, windowHeight)
	, m_shipSelect("Media/MenuInfo/shipselect.txt", windowWidth, windowHeight)
	, m_gameOverScreen("Media/MenuInfo/gameover.txt", windowWidth, windowHeight)
	, m_howToPlayScreen("Media/MenuInfo/howtoplay.txt", windowWidth, windowHeight)
	, m_pauseMenu("Media/MenuInfo/pause.txt", windowWidth, windowHeight)
	, m_previousDownKeyPressed(false)
	, m_previousUpKeyPressed(false)
	, m_desiredUpdateTime(sf::seconds(1.f / 12000.f))
	, m_timeCounter(sf::seconds(0))
	, m_FPSCounter(0)
	, m_gameWorld(windowWidth, windowHeight, &m_window)
{
	//Load fonts to be used for on screen messages
	m_initialised = m_textFont.loadFromFile("Media/Fonts/gameover.ttf");

	//Set the message text object to use the font
	m_messageText.setFont(m_textFont);
	m_messageText.setScale(0.25, 0.25);

	m_mainMenu.setPosition(m_screenWidth / 2, m_screenHeight / 2);
}

Application::~Application()
{

}

void Application::update(sf::Time& elapsedTime)
{
	//Set speed camera pans
	float cameraPanSpeed = 60.0f;

	bool validEventPoll = m_window.pollEvent(m_event);

	if ((m_event.type == sf::Event::Closed) && validEventPoll)
		m_window.close();

	//Prepare the message text and it's position
	bool currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool currentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	bool currentSpaceBarPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	

	m_window.setMouseCursorVisible(false);

	//Manages app states
	switch (m_appState)
	{
	case MAINMENU:
		selection = m_mainMenu.update(elapsedTime);

		if (selection >= 0)
		{
			if (selection == 0)
				m_appState = SHIPMENU;
			else if (selection == 1)
				m_appState = HOWTOPLAYSCREEN;
			else if (selection == 2)
				m_appState = EXITING;
		}
		break;

	case SHIPMENU:
		selection = m_shipSelect.update(elapsedTime);

		if (currentEscapeKeyPressed)
			m_appState = MAINMENU;

		if (selection >= 0)
		{
			if (selection == 0)
			{
				m_shipSelection = GNAT;
				m_gameWorld.m_playerShip->shipChoice(selection);
				m_appState = GAMEPLAYING;
			}
			else if (selection == 1)
			{
				m_shipSelection = MANTIS;
				m_gameWorld.m_playerShip->shipChoice(selection);
				m_appState = GAMEPLAYING;
			}
			//Third ship choice - Tug, to be implemented at a later date
			else if (selection == 2)
			{
				//m_shipSelection = TUG;
				//m_gameWorld.m_playerShip->shipChoice(selection);
			}
		}

		break;

	case GAMEPLAYING:
		if (currentEscapeKeyPressed)
			m_appState = PAUSESCREEN;

		//update GameWorld
		m_gameWorld.update(elapsedTime);

		if (m_gameWorld.m_playerShip->m_hull <= 0)
		{
			m_appState = GAMEOVERSCREEN;
		}

		break;

	case GAMEOVERSCREEN:
		selection = m_gameOverScreen.update(elapsedTime);
		m_gameWorld.resetGame();

		if (selection >= 0)
		{
			if (selection == 0)
			{
				m_appState = MAINMENU;
			}
			else if (selection == 1)
			{
				m_appState = EXITING;
			}
		}
		break;

	case HOWTOPLAYSCREEN:
		selection = m_howToPlayScreen.update(elapsedTime);

		if (currentEscapeKeyPressed)
			m_appState = MAINMENU;
		break;

	case PAUSESCREEN:
		selection = m_pauseMenu.update(elapsedTime);

		if (selection >= 0)
		{
			if (selection == 0)
			{
				m_appState = GAMEPLAYING;
			}
			else if (selection == 1)
			{
				m_appState = MAINMENU;
				m_gameWorld.resetGame();
			}
		}
		break;

	case EXITING:
		m_window.close();
		break;
	}

	//Navigates main menu
	m_previousUpKeyPressed = currentUpKeyPressed;
	m_previousDownKeyPressed = currentDownKeyPressed;
	m_previousSpaceBarPressed = currentSpaceBarPressed;

	m_messageText.setPosition(m_screenWidth / 2, m_screenHeight / 2);
	m_messageText.setCharacterSize(100);

	sf::FloatRect textbox = m_messageText.getLocalBounds();
	m_messageText.setOrigin(textbox.width / 2, textbox.height / 2);
}


void Application::render()
{
	m_window.clear();

	//Draws each app state
	switch (m_appState)
	{
		break;
	case MAINMENU:
		m_window.draw(m_mainMenu);
		break;
	case SHIPMENU:
		m_window.draw(m_shipSelect);
		break;
	case GAMEPLAYING:
		m_window.draw(m_gameWorld);
		break;
	case GAMEOVERSCREEN:
		m_window.draw(m_gameOverScreen);
		break;
	case HOWTOPLAYSCREEN:
		m_window.draw(m_howToPlayScreen);
		break;
	case PAUSESCREEN:
		m_window.draw(m_pauseMenu);
		break;
	case EXITING:
		break;
	}

	m_window.display();
}

void Application::run()
{
	if (!m_initialised)
		return;

	sf::Clock clock;

	//Track time since update() was last executed
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		//Get the elased time since the last loop
		sf::Time elapsedTime = clock.restart();

		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			//update application status
			//update(m_desiredUpdateTime);

			//subtract m_desiredUpdateTime from timeSinceLastUpdate
			timeSinceLastUpdate -= m_desiredUpdateTime;
		}

		//Calculate FPS
		update(elapsedTime);

		render();
	}
}
