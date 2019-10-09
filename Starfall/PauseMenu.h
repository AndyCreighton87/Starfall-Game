#ifndef PAUSEMENU
#define PAUSEMENU

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class PauseMenu :
	public sf::Drawable, public sf::Transformable
{
public:
	PauseMenu(std::string menuFileName, int& windowWidth, int& windowHeight);
	~PauseMenu();

	int						update(sf::Time& elapsedTime);

private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool					m_prevDownKeyPressed;
	bool					m_prevUpKeyPressed;
	bool					m_prevReturnKeyPressed;
	int						m_highlightIndex;

	sf::Texture				m_backgroundTexture;
	sf::Sprite				m_backgroundSprite;
	sf::FloatRect			m_backgroundRect;

	sf::Font				m_gameFont;
	sf::Color				m_highlightTextColour;
	sf::Color				m_normalTextColour;
	sf::Color				m_normalOutlineColour;
	sf::Color				m_highlightOutlineColour;

	sf::Text				m_pauseText;

	sf::Vector2f			m_menuItemBorder;
	std::vector<sf::Text>	m_menuText;

	enum MENU_ALIGNMENT
	{
		LEFT_JUSTIFIED,
		CENTRE_JUSTIFIED,
		RIGHT_JUSTIFIED
	};

	MENU_ALIGNMENT			m_menuAlignment;
};

#endif