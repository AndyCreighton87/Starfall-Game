#include "Explosion.h"

Explosion::Explosion(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
	: m_destroyAnimation(false)
{
	m_animationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	setCurrentAnimation(m_animationID);
	
	m_gameFont.loadFromFile("Media/Fonts/gameover.ttf");

	m_scoreText.setFont(m_gameFont);
	m_scoreText.setCharacterSize(120);
	m_scoreText.setStyle(sf::Text::Bold);
	m_scoreText.setFillColor(sf::Color(255, 255, 255, 255));
	m_scoreText.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_scoreText.setOutlineThickness(7.0f);
	m_scoreText.setString("1000");
}

Explosion::~Explosion()
{
}

void Explosion::update(sf::Time& elapsedTime)
{
	this->m_currentAnimation->setLoop(false);

	m_scoreText.setPosition(this->getPosition().x, this->getPosition().y - 200);

	AnimatedSpriteObject::update(elapsedTime);

	if (this->m_currentAnimation->isCompleted())
	{
		m_destroyAnimation = true;
	}
}
