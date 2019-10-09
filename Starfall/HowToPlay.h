#ifndef HOWTOPLAY
#define HOWTOPLAY

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class HowToPlay :
	public sf::Drawable, public sf::Transformable
{
public:
	HowToPlay(std::string menuFileName, int& windowWidth, int& windowHeight);
	~HowToPlay();

	int						update(sf::Time& elapsedTime);

private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture				m_backgroundTexture;
	sf::Sprite				m_backgroundSprite;
	sf::FloatRect			m_backgroundRect;

	sf::Texture				m_howToPlayTexture;
	sf::Sprite				m_howToPlaySprite;
};

#endif