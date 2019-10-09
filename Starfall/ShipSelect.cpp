#include "ShipSelect.h"

ShipSelect::ShipSelect(std::string menuFileName, int& windowWidth, int& windowHeight)
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
			m_backgroundSprite.setOrigin(0, 0);
			m_backgroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set rect texture centered at 0, 0
			m_backgroundRect.left = -static_cast<float> (textureSize.x / 2);
			m_backgroundRect.top = -static_cast<float> (textureSize.y / 2);
			m_backgroundRect.width = textureSize.x;
			m_backgroundRect.height = textureSize.y;

		}

		//Read 2nd line - container texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_containerTexture.loadFromFile(stringLine);
			m_containerSprite.setTexture(m_containerTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_containerTexture.getSize();
			m_containerSprite.setOrigin(0, 0);
			m_containerSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_containerSprite.setPosition(20, 10);
		}

		//Read 3rd line - gnat texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_gnatTexture.loadFromFile(stringLine);
			m_gnatSprite.setTexture(m_gnatTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_gnatTexture.getSize();
			m_gnatSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_gnatSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_gnatSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.35f));
		}

		//read 4th line - mantis texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_mantisTexture.loadFromFile(stringLine);
			m_mantisSprite.setTexture(m_mantisTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_mantisTexture.getSize();
			m_mantisSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_mantisSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_mantisSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.35f));
		}

		//read 5th line - tug texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_tugTexture.loadFromFile(stringLine);
			m_tugSprite.setTexture(m_tugTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_tugTexture.getSize();
			m_tugSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_tugSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_tugSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.35f));

		}

		//read 6th line - blink texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_blinkTexture.loadFromFile(stringLine);
			m_blinkSprite.setTexture(m_blinkTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_blinkTexture.getSize();
			m_blinkSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_blinkSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_blinkSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.7f));

		}

		//read 7th line - rapidFire texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_rapidFireTexture.loadFromFile(stringLine);
			m_rapidFireSprite.setTexture(m_rapidFireTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_rapidFireTexture.getSize();
			m_rapidFireSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_rapidFireSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_rapidFireSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.7f));

		}

		//read 8th line - shield texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_shieldTexture.loadFromFile(stringLine);
			m_shieldSprite.setTexture(m_shieldTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_shieldTexture.getSize();
			m_shieldSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_shieldSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_shieldSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.7f));

		}

		//read 9th line - mine texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_mineTexture.loadFromFile(stringLine);
			m_mineSprite.setTexture(m_mineTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_mineTexture.getSize();
			m_mineSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_mineSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_mineSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.7f));
		}

		//read 10th line - tractorBeam texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_tractorBeamTexture.loadFromFile(stringLine);
			m_tractorBeamSprite.setTexture(m_tractorBeamTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_tractorBeamTexture.getSize();
			m_tractorBeamSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_tractorBeamSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_tractorBeamSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.7f));

		}

		//read 11th line - ram texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_ramTexture.loadFromFile(stringLine);
			m_ramSprite.setTexture(m_ramTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_ramTexture.getSize();
			m_ramSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_ramSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_ramSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.7f));
		}



		//Read 12th line - font style
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

		//Read 13th line - text colour
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

		//Read 14th line - text outline colour
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

		//Read 15th line - text highlight colour
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

		//Read 16th line - text highlight outline colour
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

		//Read 17th line - text alignment
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

		//Read 18th line - Gnat title
		sf::Text gnatTitle;
		gnatTitle.setFont(m_gameFont);
		gnatTitle.setCharacterSize(75);
		gnatTitle.setStyle(sf::Text::Bold);
		gnatTitle.setFillColor(m_normalTextColour);
		gnatTitle.setOutlineColor(m_normalOutlineColour);
		gnatTitle.setOutlineThickness(7.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.5f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.16f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			gnatTitle.setPosition(textpos.x, textpos.y);

			gnatTitle.setString(stringLine);

			sf::FloatRect textbox = gnatTitle.getLocalBounds();

			gnatTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_gnatTitle = gnatTitle;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 19th line - mantis title
		sf::Text mantisTitle;
		mantisTitle.setFont(m_gameFont);
		mantisTitle.setCharacterSize(75);
		mantisTitle.setStyle(sf::Text::Bold);
		mantisTitle.setFillColor(m_normalTextColour);
		mantisTitle.setOutlineColor(m_normalOutlineColour);
		mantisTitle.setOutlineThickness(7.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.5f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.16f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			mantisTitle.setPosition(textpos.x, textpos.y);

			mantisTitle.setString(stringLine);

			sf::FloatRect textbox = mantisTitle.getLocalBounds();

			mantisTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_mantisTitle = mantisTitle;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 20th line - tug title
		sf::Text tugTitle;
		tugTitle.setFont(m_gameFont);
		tugTitle.setCharacterSize(75);
		tugTitle.setStyle(sf::Text::Bold);
		tugTitle.setFillColor(m_normalTextColour);
		tugTitle.setOutlineColor(m_normalOutlineColour);
		tugTitle.setOutlineThickness(7.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.5f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.16f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			tugTitle.setPosition(textpos.x, textpos.y);

			tugTitle.setString(stringLine);

			sf::FloatRect textbox = tugTitle.getLocalBounds();

			tugTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_tugTitle = tugTitle;

			textpos.x = 0;
			textpos.y = 0;

		}

		//Read 21st line - gnat hull
		sf::Text gnatHull;
		gnatHull.setFont(m_gameFont);
		gnatHull.setCharacterSize(35);
		gnatHull.setStyle(sf::Text::Bold);
		gnatHull.setFillColor(m_normalTextColour);
		gnatHull.setOutlineColor(m_normalOutlineColour);
		gnatHull.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.33f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			gnatHull.setPosition(textpos.x, textpos.y);

			gnatHull.setString(stringLine);

			sf::FloatRect textbox = gnatHull.getLocalBounds();

			gnatHull.setOrigin(textbox.width / 2, textbox.height / 2);

			m_gnatHull = gnatHull;

			textpos.x = 0;
			textpos.y = 0;

		}

		//Read 22nd line - gnat speed
		sf::Text gnatSpeed;
		gnatSpeed.setFont(m_gameFont);
		gnatSpeed.setCharacterSize(35);
		gnatSpeed.setStyle(sf::Text::Bold);
		gnatSpeed.setFillColor(m_normalTextColour);
		gnatSpeed.setOutlineColor(m_normalOutlineColour);
		gnatSpeed.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.41f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			gnatSpeed.setPosition(textpos.x, textpos.y);

			gnatSpeed.setString(stringLine);

			sf::FloatRect textbox = gnatSpeed.getLocalBounds();

			gnatSpeed.setOrigin(textbox.width / 2, textbox.height / 2);

			m_gnatSpeed = gnatSpeed;

			textpos.x = 0;
			textpos.y = 0;

		}

		//Read 23rd line - mantis stats
		sf::Text mantisHull;
		mantisHull.setFont(m_gameFont);
		mantisHull.setCharacterSize(35);
		mantisHull.setStyle(sf::Text::Bold);
		mantisHull.setFillColor(m_normalTextColour);
		mantisHull.setOutlineColor(m_normalOutlineColour);
		mantisHull.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.33f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			mantisHull.setPosition(textpos.x, textpos.y);

			mantisHull.setString(stringLine);

			sf::FloatRect textbox = mantisHull.getLocalBounds();

			mantisHull.setOrigin(textbox.width / 2, textbox.height / 2);

			m_mantisHull = mantisHull;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 24th line - mantis speed
		sf::Text mantisSpeed;
		mantisSpeed.setFont(m_gameFont);
		mantisSpeed.setCharacterSize(35);
		mantisSpeed.setStyle(sf::Text::Bold);
		mantisSpeed.setFillColor(m_normalTextColour);
		mantisSpeed.setOutlineColor(m_normalOutlineColour);
		mantisSpeed.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.41f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			mantisSpeed.setPosition(textpos.x, textpos.y);

			mantisSpeed.setString(stringLine);

			sf::FloatRect textbox = mantisSpeed.getLocalBounds();

			mantisSpeed.setOrigin(textbox.width / 2, textbox.height / 2);

			m_mantisSpeed = mantisSpeed;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 25th line - tug hull
		sf::Text tugHull;
		tugHull.setFont(m_gameFont);
		tugHull.setCharacterSize(35);
		tugHull.setStyle(sf::Text::Bold);
		tugHull.setFillColor(m_normalTextColour);
		tugHull.setOutlineColor(m_normalOutlineColour);
		tugHull.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.33f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			tugHull.setPosition(textpos.x, textpos.y);

			tugHull.setString(stringLine);

			sf::FloatRect textbox = tugHull.getLocalBounds();

			tugHull.setOrigin(textbox.width / 2, textbox.height / 2);

			m_tugHull = tugHull;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 26th line - tug speed
		sf::Text tugSpeed;
		tugSpeed.setFont(m_gameFont);
		tugSpeed.setCharacterSize(35);
		tugSpeed.setStyle(sf::Text::Bold);
		tugSpeed.setFillColor(m_normalTextColour);
		tugSpeed.setOutlineColor(m_normalOutlineColour);
		tugSpeed.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.41f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			tugSpeed.setPosition(textpos.x, textpos.y);

			tugSpeed.setString(stringLine);

			sf::FloatRect textbox = tugSpeed.getLocalBounds();

			tugSpeed.setOrigin(textbox.width / 2, textbox.height / 2);

			m_tugSpeed = tugSpeed;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 27th line - Blink title
		sf::Text blinkTitle;
		blinkTitle.setFont(m_gameFont);
		blinkTitle.setCharacterSize(35);
		blinkTitle.setStyle(sf::Text::Bold);
		blinkTitle.setFillColor(m_normalTextColour);
		blinkTitle.setOutlineColor(m_normalOutlineColour);
		blinkTitle.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.6f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			blinkTitle.setPosition(textpos.x, textpos.y);

			blinkTitle.setString(stringLine);

			sf::FloatRect textbox = blinkTitle.getLocalBounds();

			blinkTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_blinkTitle = blinkTitle;


			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 28th line - Rapid Fire title
		sf::Text rapidFireTitle;
		rapidFireTitle.setFont(m_gameFont);
		rapidFireTitle.setCharacterSize(35);
		rapidFireTitle.setStyle(sf::Text::Bold);
		rapidFireTitle.setFillColor(m_normalTextColour);
		rapidFireTitle.setOutlineColor(m_normalOutlineColour);
		rapidFireTitle.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.6f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			rapidFireTitle.setPosition(textpos.x, textpos.y);

			rapidFireTitle.setString(stringLine);

			sf::FloatRect textbox = rapidFireTitle.getLocalBounds();

			rapidFireTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_rapidFireTitle = rapidFireTitle;


			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 29th line - Shield title
		sf::Text shieldTitle;
		shieldTitle.setFont(m_gameFont);
		shieldTitle.setCharacterSize(35);
		shieldTitle.setStyle(sf::Text::Bold);
		shieldTitle.setFillColor(m_normalTextColour);
		shieldTitle.setOutlineColor(m_normalOutlineColour);
		shieldTitle.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.6f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			shieldTitle.setPosition(textpos.x, textpos.y);

			shieldTitle.setString(stringLine);

			sf::FloatRect textbox = shieldTitle.getLocalBounds();

			shieldTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_shieldTitle = shieldTitle;


			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 30th line - Mine title
		sf::Text mineTitle;
		mineTitle.setFont(m_gameFont);
		mineTitle.setCharacterSize(35);
		mineTitle.setStyle(sf::Text::Bold);
		mineTitle.setFillColor(m_normalTextColour);
		mineTitle.setOutlineColor(m_normalOutlineColour);
		mineTitle.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.6f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			mineTitle.setPosition(textpos.x, textpos.y);

			mineTitle.setString(stringLine);

			sf::FloatRect textbox = mineTitle.getLocalBounds();

			mineTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_mineTitle = mineTitle;


			textpos.x = 0;
			textpos.y = 0;

		}

		//Read 31st line - Tractor Beam title
		sf::Text tractorBeamTitle;
		tractorBeamTitle.setFont(m_gameFont);
		tractorBeamTitle.setCharacterSize(35);
		tractorBeamTitle.setStyle(sf::Text::Bold);
		tractorBeamTitle.setFillColor(m_normalTextColour);
		tractorBeamTitle.setOutlineColor(m_normalOutlineColour);
		tractorBeamTitle.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.6f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			tractorBeamTitle.setPosition(textpos.x, textpos.y);

			tractorBeamTitle.setString(stringLine);

			sf::FloatRect textbox = tractorBeamTitle.getLocalBounds();

			tractorBeamTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_tractorBeamTitle = tractorBeamTitle;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 32nd line - Ram title
		sf::Text ramTitle;
		ramTitle.setFont(m_gameFont);
		ramTitle.setCharacterSize(35);
		ramTitle.setStyle(sf::Text::Bold);
		ramTitle.setFillColor(m_normalTextColour);
		ramTitle.setOutlineColor(m_normalOutlineColour);
		ramTitle.setOutlineThickness(3.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.6f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			ramTitle.setPosition(textpos.x, textpos.y);

			ramTitle.setString(stringLine);

			sf::FloatRect textbox = ramTitle.getLocalBounds();

			ramTitle.setOrigin(textbox.width / 2, textbox.height / 2);

			m_ramTitle = ramTitle;

			textpos.x = 0;
			textpos.y = 0;

		}


		//Read 33rd line - Blink Text
		sf::Text blinkText;
		blinkText.setFont(m_gameFont);
		blinkText.setCharacterSize(20);
		blinkText.setStyle(sf::Text::Bold);
		blinkText.setFillColor(m_normalTextColour);
		blinkText.setOutlineColor(m_normalOutlineColour);
		blinkText.setOutlineThickness(2.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.8f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			blinkText.setPosition(textpos.x, textpos.y);

			blinkText.setString(stringLine);

			sf::FloatRect textbox = blinkText.getLocalBounds();

			blinkText.setOrigin(textbox.width / 2, textbox.height / 2);

			m_blinkText = blinkText;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 34th line - Rapid Fire Text
		sf::Text rapidFireText;
		rapidFireText.setFont(m_gameFont);
		rapidFireText.setCharacterSize(20);
		rapidFireText.setStyle(sf::Text::Bold);
		rapidFireText.setFillColor(m_normalTextColour);
		rapidFireText.setOutlineColor(m_normalOutlineColour);
		rapidFireText.setOutlineThickness(2.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.8f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			rapidFireText.setPosition(textpos.x, textpos.y);

			rapidFireText.setString(stringLine);

			sf::FloatRect textbox = rapidFireText.getLocalBounds();

			rapidFireText.setOrigin(textbox.width / 2, textbox.height / 2);

			m_rapidFireText = rapidFireText;

			textpos.x = 0;
			textpos.y = 0;

		}

		//Read 35th line - Shield Text
		sf::Text shieldText;
		shieldText.setFont(m_gameFont);
		shieldText.setCharacterSize(20);
		shieldText.setStyle(sf::Text::Bold);
		shieldText.setFillColor(m_normalTextColour);
		shieldText.setOutlineColor(m_normalOutlineColour);
		shieldText.setOutlineThickness(2.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.8f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			shieldText.setPosition(textpos.x, textpos.y);

			shieldText.setString(stringLine);

			sf::FloatRect textbox = shieldText.getLocalBounds();

			shieldText.setOrigin(textbox.width / 2, textbox.height / 2);

			m_shieldText = shieldText;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 36th line - Mine Text
		sf::Text mineText;
		mineText.setFont(m_gameFont);
		mineText.setCharacterSize(20);
		mineText.setStyle(sf::Text::Bold);
		mineText.setFillColor(m_normalTextColour);
		mineText.setOutlineColor(m_normalOutlineColour);
		mineText.setOutlineThickness(2.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.8f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			mineText.setPosition(textpos.x, textpos.y);

			mineText.setString(stringLine);

			sf::FloatRect textbox = mineText.getLocalBounds();

			mineText.setOrigin(textbox.width / 2, textbox.height / 2);

			m_mineText = mineText;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Read 37th line - Tractor Beam Text
		sf::Text tractorBeamText;
		tractorBeamText.setFont(m_gameFont);
		tractorBeamText.setCharacterSize(20);
		tractorBeamText.setStyle(sf::Text::Bold);
		tractorBeamText.setFillColor(m_normalTextColour);
		tractorBeamText.setOutlineColor(m_normalOutlineColour);
		tractorBeamText.setOutlineThickness(2.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.33f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.8f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			tractorBeamText.setPosition(textpos.x, textpos.y);

			tractorBeamText.setString(stringLine);

			sf::FloatRect textbox = tractorBeamText.getLocalBounds();

			tractorBeamText.setOrigin(textbox.width / 2, textbox.height / 2);

			m_tractorBeamText = tractorBeamText;

			textpos.x = 0;
			textpos.y = 0;

		}

		//Read 38th line - Ram Text
		sf::Text ramText;
		ramText.setFont(m_gameFont);
		ramText.setCharacterSize(20);
		ramText.setStyle(sf::Text::Bold);
		ramText.setFillColor(m_normalTextColour);
		ramText.setOutlineColor(m_normalOutlineColour);
		ramText.setOutlineThickness(2.0f);

		textpos.x = m_containerSprite.getPosition().x + (m_containerTexture.getSize().x * 0.66f);
		textpos.y = m_containerSprite.getPosition().y + (m_containerTexture.getSize().y * 0.8f);

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			ramText.setPosition(textpos.x, textpos.y);

			ramText.setString(stringLine);

			sf::FloatRect textbox = ramText.getLocalBounds();

			ramText.setOrigin(textbox.width / 2, textbox.height / 2);

			m_ramText = ramText;

			textpos.x = 0;
			textpos.y = 0;
		}

		//Text container

		m_menuItemBorder.x = windowWidth * 0.7f;
		m_menuItemBorder.y = windowHeight * 0.45f;

		//read 39th line - coming soon texture
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture and set sprite
			m_comingSoonTexture.loadFromFile(stringLine);
			m_comingSoonSprite.setTexture(m_comingSoonTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_comingSoonTexture.getSize();
			m_comingSoonSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_comingSoonSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//Set initally hidden
			m_comingSoonSprite.setColor(sf::Color(255, 255, 255, 0));

			//set position
			m_comingSoonSprite.setPosition(m_containerSprite.getPosition().x + (m_containerTexture.getSize().x / 2), m_containerSprite.getPosition().y + (m_containerTexture.getSize().y / 2));
		}

		//Read remaining lines - menu options
		sf::Text start;
		start.setFont(m_gameFont);
		start.setCharacterSize(75);
		start.setStyle(sf::Text::Bold);
		start.setFillColor(m_normalTextColour);
		start.setOutlineColor(m_normalOutlineColour);
		start.setOutlineThickness(7.0f);

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

				start.setOrigin(textbox.width / 2, textbox.height / 2);

				m_menuText.push_back(start);

				textpos.y += start.getLocalBounds().height * 1.2f;
			}
			else
				break;
		} while (true);

		m_highlightIndex = 0;
		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);

		m_selection = 0;

		m_prevDownKeyPressed = true;
		m_prevReturnKeyPressed = true;
		m_prevUpKeyPressed = true;

		inputFile.close();
	}
}

ShipSelect::~ShipSelect()
{
	m_menuText.clear();
}

void ShipSelect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_backgroundSprite, states);
	target.draw(m_containerSprite, states);
	target.draw(m_gnatSprite, states);
	target.draw(m_mantisSprite, states);
	target.draw(m_tugSprite, states);
	target.draw(m_blinkSprite, states);
	target.draw(m_rapidFireSprite, states);
	target.draw(m_shieldSprite, states);
	target.draw(m_mineSprite, states);
	target.draw(m_tractorBeamSprite, states);
	target.draw(m_ramSprite, states);

	target.draw(m_gnatTitle, states);
	target.draw(m_mantisTitle, states);
	target.draw(m_tugTitle, states);

	target.draw(m_gnatHull, states);
	target.draw(m_gnatSpeed, states);
	target.draw(m_mantisHull, states);
	target.draw(m_mantisSpeed, states);
	target.draw(m_tugHull, states);
	target.draw(m_tugSpeed, states);

	target.draw(m_blinkTitle, states);
	target.draw(m_rapidFireTitle, states);
	target.draw(m_shieldTitle, states);
	target.draw(m_mineTitle, states);
	target.draw(m_tractorBeamTitle, states);
	target.draw(m_ramTitle, states);

	target.draw(m_blinkText, states);
	target.draw(m_rapidFireText, states);
	target.draw(m_shieldText, states);
	target.draw(m_mineText, states);
	target.draw(m_tractorBeamText, states);
	target.draw(m_ramText, states);

	target.draw(m_comingSoonSprite, states);

	for (std::size_t i = 0; i < m_menuText.size(); ++i)
		target.draw(m_menuText[i], states);
}

int ShipSelect::update(sf::Time& elapsedTime)
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

		if (m_selection < 2)
		{
			++m_selection;
		}
		else
		{
			m_selection = 0;
		}

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

		if (m_selection > 0)
		{
			m_selection--;
		}
		else
		{
			m_selection = 2;
		}

		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
	}

	m_prevDownKeyPressed = m_currentDownKeyPressed;
	m_prevUpKeyPressed = m_currentUpKeyPressed;

	//Displays ship information
	if (m_selection == 0)
	{
		showGnat();
		hideMantis();
		hideTug();
	}
	else if (m_selection == 1)
	{
		hideGnat();
		showMantis();
		hideTug();
	}
	else if (m_selection == 2)
	{
		hideGnat();
		hideMantis();
		showTug();
	}

	bool hasSelected = false;

	if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed)
		hasSelected = true;

	m_prevReturnKeyPressed = m_currentReturnKeyPressed;

	if (hasSelected)
		return m_highlightIndex;
	else
		return -1;
}

void ShipSelect::hideGnat()
{
	m_gnatSprite.setColor(sf::Color(255, 255, 255, 0));
	m_blinkSprite.setColor(sf::Color(255, 255, 255, 0));
	m_rapidFireSprite.setColor(sf::Color(255, 255, 255, 0));

	m_gnatTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_gnatHull.setFillColor(sf::Color(255, 255, 255, 0));
	m_gnatSpeed.setFillColor(sf::Color(255, 255, 255, 0));
	m_blinkTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_blinkText.setFillColor(sf::Color(255, 255, 255, 0));
	m_rapidFireTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_rapidFireText.setFillColor(sf::Color(255, 255, 255, 0));

	m_gnatTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_gnatHull.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_gnatSpeed.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_blinkTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_blinkText.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_rapidFireTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_rapidFireText.setOutlineColor(sf::Color(0, 0, 0, 0));

	m_comingSoonSprite.setColor(sf::Color(255, 255, 255, 0));
}
void ShipSelect::showGnat()
{

	m_gnatSprite.setColor(sf::Color(255, 255, 255, 255));
	m_blinkSprite.setColor(sf::Color(255, 255, 255, 255));
	m_rapidFireSprite.setColor(sf::Color(255, 255, 255, 255));

	m_gnatTitle.setFillColor(sf::Color(255, 255, 255, 255));
	m_gnatHull.setFillColor(sf::Color(255, 255, 255, 255));
	m_gnatSpeed.setFillColor(sf::Color(255, 255, 255, 255));
	m_blinkTitle.setFillColor(sf::Color(255, 255, 255, 255));
	m_blinkText.setFillColor(sf::Color(255, 255, 255, 255));
	m_rapidFireTitle.setFillColor(sf::Color(255, 255, 255, 255));
	m_rapidFireText.setFillColor(sf::Color(255, 255, 255, 255));

	m_gnatTitle.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_gnatHull.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_gnatSpeed.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_blinkTitle.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_blinkText.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_rapidFireTitle.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_rapidFireText.setOutlineColor(sf::Color(0, 0, 0, 255));

	m_comingSoonSprite.setColor(sf::Color(255, 255, 255, 0));
}
void ShipSelect::hideMantis()
{
	m_mantisSprite.setColor(sf::Color(255, 255, 255, 0));
	m_shieldSprite.setColor(sf::Color(255, 255, 255, 0));
	m_mineSprite.setColor(sf::Color(255, 255, 255, 0));

	m_mantisTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_mantisHull.setFillColor(sf::Color(255, 255, 255, 0));
	m_mantisSpeed.setFillColor(sf::Color(255, 255, 255, 0));
	m_shieldTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_shieldText.setFillColor(sf::Color(255, 255, 255, 0));
	m_mineTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_mineText.setFillColor(sf::Color(255, 255, 255, 0));

	m_mantisTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_mantisHull.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_mantisSpeed.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_shieldTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_shieldText.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_mineTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_mineText.setOutlineColor(sf::Color(0, 0, 0, 0));

	m_comingSoonSprite.setColor(sf::Color(255, 255, 255, 0));
}
void ShipSelect::showMantis()
{
	m_mantisSprite.setColor(sf::Color(255, 255, 255, 255));
	m_shieldSprite.setColor(sf::Color(255, 255, 255, 255));
	m_mineSprite.setColor(sf::Color(255, 255, 255, 255));

	m_mantisTitle.setFillColor(sf::Color(255, 255, 255, 255));
	m_mantisHull.setFillColor(sf::Color(255, 255, 255, 255));
	m_mantisSpeed.setFillColor(sf::Color(255, 255, 255, 255));
	m_shieldTitle.setFillColor(sf::Color(255, 255, 255, 255));
	m_shieldText.setFillColor(sf::Color(255, 255, 255, 255));
	m_mineTitle.setFillColor(sf::Color(255, 255, 255, 255));
	m_mineText.setFillColor(sf::Color(255, 255, 255, 255));

	m_mantisTitle.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_mantisHull.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_mantisSpeed.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_shieldTitle.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_shieldText.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_mineTitle.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_mineText.setOutlineColor(sf::Color(0, 0, 0, 255));

	m_comingSoonSprite.setColor(sf::Color(255, 255, 255, 0));
}
void ShipSelect::hideTug()
{
	m_tugSprite.setColor(sf::Color(255, 255, 255, 0));
	m_tractorBeamSprite.setColor(sf::Color(255, 255, 255, 0));
	m_ramSprite.setColor(sf::Color(255, 255, 255, 0));

	m_tugTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_tugHull.setFillColor(sf::Color(255, 255, 255, 0));
	m_tugSpeed.setFillColor(sf::Color(255, 255, 255, 0));
	m_tractorBeamTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_tractorBeamText.setFillColor(sf::Color(255, 255, 255, 0));
	m_ramTitle.setFillColor(sf::Color(255, 255, 255, 0));
	m_ramText.setFillColor(sf::Color(255, 255, 255, 0));

	m_tugTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_tugHull.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_tugSpeed.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_tractorBeamTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_tractorBeamText.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_ramTitle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_ramText.setOutlineColor(sf::Color(0, 0, 0, 0));

	m_comingSoonSprite.setColor(sf::Color(255, 255, 255, 0));
}
void ShipSelect::showTug()
{
	m_tugSprite.setColor(sf::Color(255, 255, 255, 127));
	m_tractorBeamSprite.setColor(sf::Color(255, 255, 255, 127));
	m_ramSprite.setColor(sf::Color(255, 255, 255, 127));

	m_tugTitle.setFillColor(sf::Color(255, 255, 255, 127));
	m_tugHull.setFillColor(sf::Color(255, 255, 255, 127));
	m_tugSpeed.setFillColor(sf::Color(255, 255, 255, 127));
	m_tractorBeamTitle.setFillColor(sf::Color(255, 255, 255, 127));
	m_tractorBeamText.setFillColor(sf::Color(255, 255, 255, 127));
	m_ramTitle.setFillColor(sf::Color(255, 255, 255, 127));
	m_ramText.setFillColor(sf::Color(255, 255, 255, 127));

	m_tugTitle.setOutlineColor(sf::Color(0, 0, 0, 127));
	m_tugHull.setOutlineColor(sf::Color(0, 0, 0, 127));
	m_tugSpeed.setOutlineColor(sf::Color(0, 0, 0, 127));
	m_tractorBeamTitle.setOutlineColor(sf::Color(0, 0, 0, 127));
	m_tractorBeamText.setOutlineColor(sf::Color(0, 0, 0, 127));
	m_ramTitle.setOutlineColor(sf::Color(0, 0, 0, 127));
	m_ramText.setOutlineColor(sf::Color(0, 0, 0, 127));

	m_comingSoonSprite.setColor(sf::Color(255, 255, 255, 255));
}
