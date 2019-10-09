#ifndef EXPLOSION
#define EXPLOSION

#include <string>
#include "AnimatedSpriteObject.h"

class Explosion :
	public AnimatedSpriteObject
{
public:
	Explosion(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	~Explosion();

	virtual void		update(sf::Time& elapsedTime);

	bool				m_destroyAnimation;

	sf::Text			m_scoreText;

private:
	int					m_animationID;

	sf::Font			m_gameFont;
};

#endif