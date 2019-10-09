#include "AnimatedSpriteObject.h"

AnimatedSpriteObject::AnimatedSpriteObject()
	: m_currentAnimation{ NULL }
	, m_isPaused(false)
	, m_currentAnimationID(-1)
{
}

AnimatedSpriteObject::~AnimatedSpriteObject()
{
	//Delete texture objects in lists
	for (std::vector<sf::Texture*>::iterator it = m_spriteTextureList.begin(); it != m_spriteTextureList.end(); ++it)
	{
		delete (*it);
	}
	m_spriteTextureList.clear();

	//Delete animation objects in list
	for (std::vector<SpriteAnimation*>::iterator it = m_animatedSpriteList.begin(); it != m_animatedSpriteList.end(); ++it)
	{
		delete (*it);
	}
	m_animatedSpriteList.clear();
}

int AnimatedSpriteObject::addAnimation(std::string spriteSheetFileName, std::string spriteInfoFileName, float animationTime)
{
	//create new texture object
	sf::Texture* spriteTexture = new sf::Texture();

	//Load texture file
	if (!spriteTexture->loadFromFile(spriteSheetFileName))
	{
		return -1;
	}

	//Store texture in list
	m_spriteTextureList.push_back(spriteTexture);

	//Create a new animation
	SpriteAnimation* animation = new SpriteAnimation();

	//Store address of texture in animation
	animation->setSpriteSheet(spriteTexture);

	//Loading sequences of frames
	std::string left;
	std::string top;
	std::string width;
	std::string height;
	std::string xcentre;
	std::string ycentre;

	//store as int
	int ileft, itop, iwidth, iheight, ixcentre, iycentre;

	int frameCounter = 0;

	std::ifstream inputFile(spriteInfoFileName);

	if (inputFile.is_open())
	{
		do
		{
			std::string stringLine;
			std::getline(inputFile, stringLine);

			if (inputFile.good())
			{
				//Line read successfully - split the result into 6
				std::istringstream stringStream(stringLine);
				stringStream >> left;
				stringStream >> top;
				stringStream >> width;
				stringStream >> height;
				stringStream >> xcentre;
				stringStream >> ycentre;

				ileft = std::stoi(left);
				itop = std::stoi(top);
				iwidth = std::stoi(width);
				iheight = std::stoi(height);
				ixcentre = std::stoi(xcentre);
				iycentre = std::stoi(ycentre);

				//Use them as animation frame
				animation->addFrame(sf::IntRect(ileft, itop, iwidth, iheight), sf::Vector2f(ixcentre - ileft, iycentre - itop));

				//Keep track of how many frames
				++frameCounter;
			}
			else
				break;
		} while (true);

		inputFile.close();
	}

	if (frameCounter > 0)
	{
		animation->setFrameTime(animationTime / frameCounter);
		m_animatedSpriteList.push_back(animation);
		m_initalised = true;
		return m_animatedSpriteList.size() - 1;
	}
	else
		return -1;

}
void AnimatedSpriteObject::setCurrentAnimation(int& animationIndex)
{
	SpriteAnimation* newAnimation = m_animatedSpriteList[animationIndex];

	if (newAnimation)
	{
		if (m_currentAnimation != newAnimation)
		{
			m_currentAnimation = newAnimation;
			m_spriteTexture = m_currentAnimation->getSpriteSheet();
			m_currentAnimation->resetCurrentAnimation();
			m_currentAnimation->getCurrentFrame(&m_textureRectangle, &m_spriteOrigin);
			m_currentTime = 0;
		}
	}
}

SpriteAnimation* AnimatedSpriteObject::getCurrentAnimation()
{
	return m_currentAnimation;
}

void AnimatedSpriteObject::play()
{
	m_isPaused = false;
}

void AnimatedSpriteObject::pause()
{
	m_isPaused = true;
}

void AnimatedSpriteObject::stop()
{
	m_isPaused = true;
	m_currentTime = 0;
}

void AnimatedSpriteObject::update(sf::Time& elapsedTime)
{
	//if not paused and have current valid animation
	if (!m_isPaused && m_currentAnimation)
	{
		float frameTime = m_currentAnimation->getTimePerFrame();

		//add elapsed time
		m_currentTime += elapsedTime.asSeconds();

		//if current time larger than fram time, advance one frame
		if (m_currentTime >= frameTime)
		{
			m_currentAnimation->incrementFrameNumber();
			m_currentAnimation->getCurrentFrame(&m_textureRectangle, &m_spriteOrigin);
			m_currentTime = m_currentTime - frameTime;
		}
	}
	SpriteObject::update(elapsedTime);
}