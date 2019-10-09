#include "EffectsAnimations.h"

EffectsAnimations::EffectsAnimations(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
	: m_destroyAnimation(false)
{
	m_animationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	setCurrentAnimation(m_animationID);
}

EffectsAnimations::~EffectsAnimations()
{
}

void EffectsAnimations::update(sf::Time& elapsedTime)
{
	this->m_currentAnimation->setLoop(false);

	AnimatedSpriteObject::update(elapsedTime);

	if (this->m_currentAnimation->isCompleted())
	{
		m_destroyAnimation = true;
	}
}
