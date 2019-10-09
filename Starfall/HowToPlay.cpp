#include "HowToPlay.h"

HowToPlay::HowToPlay(std::string menuFileName, int & windowWidth, int & windowHeight)
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
			m_howToPlayTexture.loadFromFile(stringLine);
			m_howToPlaySprite.setTexture(m_howToPlayTexture);

			//set origin, texture rect and position
			sf::Vector2u textureSize = m_howToPlayTexture.getSize();
			m_howToPlaySprite.setOrigin(0, 0);
			m_howToPlaySprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

			//set position
			m_howToPlaySprite.setPosition(20, 10);
		}
	}
}

HowToPlay::~HowToPlay()
{
}

int HowToPlay::update(sf::Time & elapsedTime)
{
	return -1;
}

void HowToPlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_backgroundSprite, states);
	target.draw(m_howToPlaySprite, states);
}
