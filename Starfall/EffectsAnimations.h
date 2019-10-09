#ifndef EFFECTSANIMATIONS
#define EFFECTSANIMATIONS

#include "AnimatedSpriteObject.h"

class EffectsAnimations :
	public AnimatedSpriteObject
{
public:
	EffectsAnimations(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	~EffectsAnimations();

	virtual void		update(sf::Time& elapsedTime);
	bool				m_destroyAnimation;

private:
	int					m_animationID;
};

#endif
