#ifndef ANIMATEDSPRITEOBJECT
#define ANIMATEDSPRITEOBJECT

#include "SpriteObject.h"
#include "SpriteAnimation.h"

class AnimatedSpriteObject :
	public SpriteObject
{
public:
	AnimatedSpriteObject();
	virtual ~AnimatedSpriteObject();

	virtual void					update(sf::Time& elapsedTime);
	void							play();
	void							pause();
	void							stop();
	void							setCurrentAnimation(int& animationIndex);
	int								addAnimation(std::string spriteSheerFilename, std::string spriteInfoFilename, float animationTime);

	SpriteAnimation*				getCurrentAnimation();

private:
	bool							m_isPaused;
	int								m_currentAnimationID;
	float							m_currentTime;

	std::vector<sf::Texture*>		m_spriteTextureList;

protected:
	std::vector<SpriteAnimation*>	m_animatedSpriteList;
	SpriteAnimation*				m_currentAnimation;
};

#endif
