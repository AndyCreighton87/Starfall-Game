#ifndef SPRITEOBJECT
#define SPRITEOBJECT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Maths.h"

class SpriteObject :
	public sf::Drawable, public sf::Transformable
{
public:
	SpriteObject();
	virtual ~SpriteObject();

	virtual void			update(sf::Time& elapsedtime);
	void					setColour(const sf::Color& colour);

	bool					setDefaultTexture(std::string textureFileName);
	bool					setDefaultTexture(std::string textureFileName, std::string spriteInfoFilename);
	bool					checkCollision(sf::Vector2f firstPosition, sf::Vector2f secondPosition, float radius);

	sf::Vector2f			getWorldPosition();
	sf::Vector2f			getScreenPosition(sf::Transform cameraScreenTransform);

	sf::FloatRect			getLocalBounds() const;
	sf::FloatRect			getGlobalBounds() const;

private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture*			m_defaultTexture;

	Maths					m_maths;

protected:
	bool					m_initalised;

	sf::Sprite				m_sprite;
	sf::Texture*			m_spriteTexture;
	sf::IntRect				m_textureRectangle;
	sf::Vector2f			m_spriteOrigin;
};

#endif