#include "HUD.h"

HUD::HUD(std::string menuFileName, int windowWidth, int windowHeight)
	: m_gameStarted(false)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	std::ifstream inputFile(menuFileName);

	if (inputFile.is_open())
	{
		std::string stringLine;

		//Read 1st line - Blink texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_blinkTexture.loadFromFile(stringLine);
			m_blinkSprite.setTexture(m_blinkTexture);
		}

		//Read 2nd line - Rapid Fire texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_rapidFireTexture.loadFromFile(stringLine);
			m_rapidFireSprite.setTexture(m_rapidFireTexture);
		}

		//Read 3rd line - Shield texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_shieldTexture.loadFromFile(stringLine);
			m_shieldSprite.setTexture(m_shieldTexture);
		}

		//Read 4th line - Mine texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_mineTexture.loadFromFile(stringLine);
			m_mineSprite.setTexture(m_mineTexture);
		}

		//Read 5th line - Tractor Beam texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_tractorBeamTexture.loadFromFile(stringLine);
			m_tractorBeamSprite.setTexture(m_tractorBeamTexture);
		}

		//Read 6th line - Ram texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_ramTexture.loadFromFile(stringLine);
			m_ramSprite.setTexture(m_ramTexture);
		}

		//Read 7th line - Font
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_font.loadFromFile(stringLine);
		}

		std::string redString;
		std::string greenString;
		std::string blueString;

		int redInt;
		int greenInt;
		int blueInt;

		//Read 8th line - Hull + Score text colour
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

			m_hudTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//Read 9th line - text colour
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

			m_textColour = sf::Color(redInt, greenInt, blueInt);
		}

		//Read 10th line - text outline colour
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

			m_textOutline = sf::Color(redInt, greenInt, blueInt);
		}

		//Read 11th line - Blink title
		sf::Text blinkTitle;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			blinkTitle.setString(stringLine);

			m_blinkTitle = blinkTitle;
		}

		//Read 12th line - Rapid Fire title
		sf::Text rapidFireTitle;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			rapidFireTitle.setString(stringLine);

			m_rapidFireTitle = rapidFireTitle;
		}

		//Read 13th line - Shield title
		sf::Text shieldTitle;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			shieldTitle.setString(stringLine);;

			m_shieldTitle = shieldTitle;
		}

		//Read 14th line - Mine title
		sf::Text mineTitle;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			mineTitle.setString(stringLine);


			m_mineTitle = mineTitle;
		}

		//Read 15th line - Tractor Beam title
		sf::Text tractorBeamTitle;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{

			tractorBeamTitle.setString(stringLine);

			m_tractorBeamTitle = tractorBeamTitle;
		}

		//Read 16th line - Ram title
		sf::Text ramTitle;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			ramTitle.setString(stringLine);

			m_ramTitle = ramTitle;
		}

		//Read 17th line - Hull Text
		m_hull.setFont(m_font);
		m_hull.setCharacterSize(100);
		m_hull.setFillColor(m_hudTextColour);
		m_hull.setOutlineColor(m_textOutline);
		m_hull.setOutlineThickness(7.0f);
		m_hull.setPosition(windowWidth * 0.05f, windowHeight * 0.05f);
		m_hull.setString("Hull: ");
		textbox = m_hull.getLocalBounds();
		m_hull.setOrigin(0, textbox.height / 2);


		//Read 18th line - Score text
		m_score.setFont(m_font);
		m_score.setCharacterSize(100);
		m_score.setFillColor(m_hudTextColour);
		m_score.setOutlineColor(m_textOutline);
		m_score.setOutlineThickness(7.0f);
		m_score.setPosition(windowWidth * 0.95f, windowHeight * 0.05f);
		m_score.setString("Score: ");
		textbox = m_score.getLocalBounds();
		m_score.setOrigin(textbox.width, textbox.height / 2);
	}
}

HUD::~HUD()
{
}

void HUD::update(sf::Time & elapsedTime, bool ability1Ready, bool ability2Ready, int hull, int score)
{
	if (ability1Ready)
	{
		m_ability1Sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		m_ability1Sprite.setColor(sf::Color(255, 255, 255, 64));
	}

	if (ability2Ready)
	{
		m_ability2Sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		m_ability2Sprite.setColor(sf::Color(255, 255, 255, 64));
	}
	m_hull.setString("Hull: ");
	m_score.setString("Score: ");
	m_hull.setString(m_hull.getString() + std::to_string(hull));
	m_score.setString(m_score.getString() + std::to_string(score));
	
	textbox = m_score.getLocalBounds();
	m_score.setOrigin(textbox.width, textbox.height / 2);
	m_score.setPosition(m_windowWidth * 0.95f, m_windowHeight * 0.05f);
}

void HUD::SetAbilities(int selection, int hull)
{
	//Sets sprites based on the ship selected
	switch (selection)
	{
	case 0:
		m_ability1Sprite = m_blinkSprite;
		m_ability1Text = m_blinkTitle;
		m_ability2Sprite = m_rapidFireSprite;
		m_ability2Text = m_rapidFireTitle;
		break;

	case 1:
		m_ability1Sprite = m_shieldSprite;
		m_ability1Text = m_shieldTitle;
		m_ability2Sprite = m_mineSprite;
		m_ability2Text = m_mineTitle;
		break;

	case 2:
		m_ability1Sprite = m_tractorBeamSprite;
		m_ability1Text = m_tractorBeamTitle;
		m_ability2Sprite = m_ramSprite;
		m_ability2Text = m_ramTitle;
		break;
	}

	
	//set origin, texture rect and position
	m_ability1Sprite.setOrigin(m_ability1Sprite.getLocalBounds().width / 2, m_ability1Sprite.getLocalBounds().height / 2);
	m_ability1Sprite.setTextureRect(sf::IntRect(0, 0, m_ability1Sprite.getLocalBounds().width, m_ability1Sprite.getLocalBounds().height));
	//set position
	m_ability1Sprite.setPosition((m_windowWidth / 2) - 200, m_windowHeight * 0.9f);

	//set origin, texture rect and position
	m_ability2Sprite.setOrigin(m_ability2Sprite.getLocalBounds().width / 2, m_ability2Sprite.getLocalBounds().height / 2);
	m_ability2Sprite.setTextureRect(sf::IntRect(0, 0, m_ability2Sprite.getLocalBounds().width, m_ability2Sprite.getLocalBounds().height));
	//set position
	m_ability2Sprite.setPosition((m_windowWidth / 2) + 200, m_windowHeight * 0.9f);

	m_ability1Text.setFont(m_font);
	m_ability1Text.setCharacterSize(45);
	m_ability1Text.setFillColor(m_textColour);
	m_ability1Text.setOutlineColor(m_textOutline);
	m_ability1Text.setOutlineThickness(3.0f);
	m_ability1Text.setPosition(m_ability1Sprite.getPosition().x, m_ability1Sprite.getPosition().y - 100);
	textbox = m_ability1Text.getLocalBounds();
	m_ability1Text.setOrigin(textbox.width / 2, textbox.height / 2);

	m_ability2Text.setFont(m_font);
	m_ability2Text.setCharacterSize(45);
	m_ability2Text.setFillColor(m_textColour);
	m_ability2Text.setOutlineColor(m_textOutline);
	m_ability2Text.setOutlineThickness(3.0f);
	m_ability2Text.setPosition(m_ability2Sprite.getPosition().x, m_ability2Sprite.getPosition().y - 100);
	textbox = m_ability2Text.getLocalBounds();
	m_ability2Text.setOrigin(textbox.width / 2, textbox.height / 2);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_hull);
	target.draw(m_score);

	target.draw(m_ability1Sprite);
	target.draw(m_ability1Text);
	target.draw(m_ability2Sprite);
	target.draw(m_ability2Text);
}