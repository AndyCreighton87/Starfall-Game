#include "SpriteObject.h"

SpriteObject::SpriteObject()
	: m_initalised(false)
{
	m_defaultTexture = NULL;
}

SpriteObject::~SpriteObject()
{
	if (m_defaultTexture != NULL)
		delete m_defaultTexture;
}

bool SpriteObject::setDefaultTexture(std::string textureFileName)
{
	if (m_defaultTexture != NULL)
		delete m_defaultTexture;

	m_defaultTexture = new sf::Texture();

	if (!m_defaultTexture->loadFromFile(textureFileName))
	{
		//Failed to load texture file
		m_initalised = false;
		delete m_defaultTexture;
		m_defaultTexture = NULL;
		return false;
	}

	//Successfully loaded texture
	m_spriteTexture = m_defaultTexture;

	//Set origin and rect
	m_spriteOrigin = sf::Vector2f(m_defaultTexture->getSize().x / 2, m_defaultTexture->getSize().y / 2);
	m_textureRectangle = sf::IntRect(0, 0, m_defaultTexture->getSize().x, m_defaultTexture->getSize().y);

	m_initalised = true;
	return true;
}

bool SpriteObject::setDefaultTexture(std::string textureFileName, std::string spriteInfoFilename)
{

	if (m_defaultTexture != NULL)
		delete m_defaultTexture;

	m_defaultTexture = new sf::Texture();

	if (!m_defaultTexture->loadFromFile(textureFileName))
	{
		//Failed to load texture file
		m_initalised = false;
		delete m_defaultTexture;
		m_defaultTexture = NULL;
		return false;
	}

	//Successfully loaded texture
	m_spriteTexture = m_defaultTexture;

	//Temp variables to store characters from info file
	std::string s_left, s_top, s_width, s_height, s_xcentre, s_ycentre;
	int i_left, i_top, i_width, i_height, i_xcentre, i_ycentre;

	//Open sprite info file
	std::ifstream inputFile(spriteInfoFilename);

	if (inputFile.is_open())
	{
		//Read a line
		std::string stringLine;
		std::getline(inputFile, stringLine);

		if (inputFile.good())
		{
			//Seperate line into 6 strings
			std::istringstream stringStream(stringLine);
			stringStream >> s_left;
			stringStream >> s_top;
			stringStream >> s_width;
			stringStream >> s_height;
			stringStream >> s_xcentre;
			stringStream >> s_ycentre;

			//Convert into Integers;
			i_left = std::stoi(s_left);
			i_top = std::stoi(s_top);
			i_width = std::stoi(s_width);
			i_height = std::stoi(s_height);
			i_xcentre = std::stoi(s_xcentre);
			i_ycentre = std::stoi(s_ycentre);
		}

		m_spriteOrigin = sf::Vector2f(i_xcentre - i_left, i_ycentre - i_top);
		m_textureRectangle = sf::IntRect(i_left, i_top, i_width, i_height);

		inputFile.close();
	}

	m_initalised = true;
	return true;
}

void SpriteObject::setColour(const sf::Color& colour)
{
	m_sprite.setColor(colour);
}

sf::FloatRect SpriteObject::getLocalBounds() const
{
	float left = static_cast<float> (-m_spriteOrigin.x);
	float top = static_cast<float> (-m_spriteOrigin.y);
	float width = static_cast<float> (m_textureRectangle.width);
	float height = static_cast<float> (m_textureRectangle.height);

	return sf::FloatRect(left, top, width, height);
}

sf::FloatRect SpriteObject::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

sf::Vector2f SpriteObject::getWorldPosition()
{
	return getTransform().transformPoint(0, 0);
}

sf::Vector2f SpriteObject::getScreenPosition(sf::Transform ViewProjTransform)
{
	sf::Transform WorldViewProjTransform = ViewProjTransform * getTransform();
	return WorldViewProjTransform * sf::Vector2f();
}

bool SpriteObject::checkCollision(sf::Vector2f firstPosition, sf::Vector2f secondPosition, float radius)
{
	//Get enemyShip current location
	sf::Vector2f vector = firstPosition - secondPosition;

	//Calculate distance between playerShip and enemyShip (L2 norm)
	float distance = m_maths.L2Norm(vector);

	if (distance < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SpriteObject::update(sf::Time& elapsedTime)
{
	if (!m_initalised)
		return;

	//Assign texture to sprite
	if (m_spriteTexture != NULL)
		m_sprite.setTexture(*m_spriteTexture);

	//Set sprite texture rect
	m_sprite.setTextureRect(m_textureRectangle);

	//Set sprites origin
	m_sprite.setOrigin(m_spriteOrigin);
}

void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}