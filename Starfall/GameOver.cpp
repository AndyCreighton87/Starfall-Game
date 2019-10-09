#include "GameOver.h"

GameOver::GameOver(std::string menuFileName, int& windowWidth, int& windowHeight)
{
	std::ifstream inputFile(menuFileName);

	if (inputFile.is_open())
	{
		std::string stringLine;

		//Read 1st line - bg texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_backgroundTexture.loadFromFile(stringLine);
			m_backgroundSprite.setTexture(m_backgroundTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_backgroundTexture.getSize();
			m_backgroundSprite.setOrigin(0,0);
			m_backgroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set rect texture centered at 0, 0
			m_backgroundRect.left = -static_cast<float> (textureSize.x / 2);
			m_backgroundRect.top = -static_cast<float> (textureSize.y / 2);
			m_backgroundRect.width = textureSize.x;
			m_backgroundRect.height = textureSize.y;
		}

		//read 2nd line - game over text
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_gameOverTexture.loadFromFile(stringLine);
			m_gameOverSprite.setTexture(m_gameOverTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_gameOverTexture.getSize();
			m_gameOverSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_gameOverSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_gameOverSprite.setPosition(windowWidth * 0.5f, windowHeight * 0.33f);
		}

		//Read 3rd line - font style
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_gameFont.loadFromFile(stringLine);
		}

		std::string redString;
		std::string greenString;
		std::string blueString;

		int redInt;
		int greenInt;
		int blueInt;

		//Read 4th line - text colour
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//seperate string
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//convert to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//Read 5th line - text outline colour
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalOutlineColour = sf::Color(redInt, greenInt, blueInt);
		}

		//Read 6th line - text highlight colour
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//Read 7th line - text highlight outline colour
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightOutlineColour = sf::Color(redInt, greenInt, blueInt);
		}

		//Read 8th line - container
		m_menuItemBorder.x = windowWidth * 0.5f;
		m_menuItemBorder.y = windowHeight * 0.66f;

		//Read 8th line - text alignment
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED"))
				m_menuAlignment = LEFT_JUSTIFIED;
			else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED"))
				m_menuAlignment = CENTRE_JUSTIFIED;
			else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED"))
				m_menuAlignment = RIGHT_JUSTIFIED;
		}

		//Read remaining lines - menu options
		sf::Text start;
		start.setFont(m_gameFont);
		start.setCharacterSize(75);
		start.setStyle(sf::Text::Bold);
		start.setFillColor(m_normalTextColour);
		start.setOutlineColor(m_normalOutlineColour);
		start.setOutlineThickness(7.0f);

		sf::Vector2f textpos;

		if (m_menuAlignment == CENTRE_JUSTIFIED)
		{
			textpos.x = m_menuItemBorder.x;
			textpos.y = m_menuItemBorder.y;
		}
		else if (m_menuAlignment == LEFT_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left + m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}
		else if (m_menuAlignment == RIGHT_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left + m_backgroundRect.width - m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}

		do
		{
			std::getline(inputFile, stringLine);
			if (inputFile.good())
			{
				start.setPosition(textpos.x, textpos.y);

				start.setString(stringLine);

				sf::FloatRect textbox = start.getLocalBounds();

				if (m_menuAlignment == CENTRE_JUSTIFIED)
				{
					start.setOrigin(textbox.width / 2, textbox.height / 2);
				}
				else if (m_menuAlignment == LEFT_JUSTIFIED)
				{
					start.setOrigin(0, textbox.height / 2);
				}
				else if (m_menuAlignment == RIGHT_JUSTIFIED)
				{
					start.setOrigin(textbox.width / 2, 0);
				}

				m_menuText.push_back(start);

				textpos.y += start.getLocalBounds().height * 1.2f;
			}
			else
				break;
		} while (true);

		m_highlightIndex = 0;
		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);

		m_prevDownKeyPressed = true;
		m_prevReturnKeyPressed = true;
		m_prevUpKeyPressed = true;

		inputFile.close();
	}
}


GameOver::~GameOver()
{
	m_menuText.clear();
}

void GameOver::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_backgroundSprite, states);
	target.draw(m_gameOverSprite, states);

	for (std::size_t i = 0; i < m_menuText.size(); ++i)
		target.draw(m_menuText[i], states);
}

int GameOver::update(sf::Time& elapsedTime)
{
	//Manages menu selection
	bool m_currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool m_currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool m_currentReturnKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

	if (m_currentDownKeyPressed && !m_prevDownKeyPressed)
	{
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		++m_highlightIndex;
		m_highlightIndex = m_highlightIndex % m_menuText.size();

		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
	}
	else if (m_currentUpKeyPressed && !m_prevUpKeyPressed)
	{
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		m_highlightIndex--;
		if (m_highlightIndex < 0)
			m_highlightIndex = m_highlightIndex + m_menuText.size();

		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
	}

	m_prevDownKeyPressed = m_currentDownKeyPressed;
	m_prevUpKeyPressed = m_currentUpKeyPressed;

	bool hasSelected = false;

	if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed)
		hasSelected = true;

	m_prevReturnKeyPressed = m_currentReturnKeyPressed;

	if (hasSelected)
		return m_highlightIndex;
	else
		return -1;
}
