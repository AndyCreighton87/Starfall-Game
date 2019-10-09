#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation()
	: m_currentFrameNumber(0)
	, m_canbeInterrupted(true)
	, m_isLoop(true)
{
}

SpriteAnimation::~SpriteAnimation()
{
	//Clears lists of rects and centres
	m_frameCentreList.clear();
	m_frameRectangleList.clear();
}

void SpriteAnimation::setSpriteSheet(sf::Texture* spriteTexture)
{
	//Store memory address of texture
	m_spritesheet = spriteTexture;
}

sf::Texture* SpriteAnimation::getSpriteSheet()
{
	//Return address of texture used
	return m_spritesheet;
}

void SpriteAnimation::addFrame(sf::IntRect textureRect, sf::Vector2f centre)
{
	//Add a frame (rect and centre)
	m_frameRectangleList.push_back(textureRect);
	m_frameCentreList.push_back(centre);
}

int SpriteAnimation::getNumberOfFrames()
{
	//Returns number of frames in animation
	return m_frameRectangleList.size();
}

bool SpriteAnimation::getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre)
{
	//Returns current frame info
	if ((m_currentFrameNumber < 0) || (m_currentFrameNumber >= m_frameRectangleList.size()))
	{
		//Out of bounds position is supplied
		return false;
	}

	//Retrieve the rect and centre data
	sf::IntRect irect = m_frameRectangleList[m_currentFrameNumber];
	sf::Vector2f icentre = m_frameCentreList[m_currentFrameNumber];

	//Copy info over
	rect->left = irect.left;
	rect->top = irect.top;
	rect->width = irect.width;
	rect->height = irect.height;

	centre->x = icentre.x;
	centre->y = icentre.y;

	return true;
}

int SpriteAnimation::getCurrentFrameNumber()
{
	return m_currentFrameNumber;
}

void SpriteAnimation::resetCurrentAnimation()
{
	m_currentFrameNumber = 0;
}

void SpriteAnimation::setFrameTime(float timePerFrame)
{
	//Set delay between showing consecutive frames
	m_timePerFrame = timePerFrame;
}

float SpriteAnimation::getTimePerFrame()
{
	//Returns delays between frames
	return m_timePerFrame;
}

void SpriteAnimation::incrementFrameNumber()
{
	++m_currentFrameNumber;
	if (m_currentFrameNumber >= m_frameRectangleList.size() - 1)
	{
		if (m_isLoop)
			resetCurrentAnimation();
		else
			m_currentFrameNumber = m_frameRectangleList.size() - 1;
	}
}

bool SpriteAnimation::isCompleted()
{
	//Check if animation is completed
	if (m_currentFrameNumber >= m_frameRectangleList.size() - 1)
		return true;
	else
		return false;
}

bool SpriteAnimation::isLooped() const
{
	return m_isLoop;
}

void SpriteAnimation::setLoop(bool loop)
{
	m_isLoop = loop;
}

bool SpriteAnimation::canBeInterrupted() const
{
	return m_canbeInterrupted;
}

void SpriteAnimation::setCanBeInterrupted(bool trueorfalse)
{
	m_canbeInterrupted = trueorfalse;
}