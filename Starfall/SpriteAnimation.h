#ifndef SPRITEANIMATION
#define SPRITEANIMATION

#include <SFML/Graphics.hpp>
#include "SpriteAnimation.h"

class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();

	void			setSpriteSheet(sf::Texture* spriteTexture);	
	void			addFrame(sf::IntRect textureRect, sf::Vector2f centre);
	void			setFrameTime(float timePerFrame);
	void			setLoop(bool loop);
	void			setCanBeInterrupted(bool trueorfalse);
	void			incrementFrameNumber();
	void			resetCurrentAnimation();

	bool			getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre);
	bool			isLooped() const;
	bool			canBeInterrupted() const;
	bool			isCompleted();
	bool			m_isLoop;

	int				getNumberOfFrames();
	int				getCurrentFrameNumber();

	float			getTimePerFrame();
	
	sf::Texture*	getSpriteSheet();

private:
	
	bool			m_canbeInterrupted;
	int				m_currentFrameNumber;
	float			m_timePerFrame;

	std::vector<sf::IntRect>		m_frameRectangleList;
	std::vector<sf::Vector2f>		m_frameCentreList;

	sf::Texture*	m_spritesheet;
};
#endif