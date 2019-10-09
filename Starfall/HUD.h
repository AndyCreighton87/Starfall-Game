#ifndef HUDUI
#define HUDUI

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class HUD :
	public sf::Drawable, public sf::Transformable
{
public:
	HUD(std::string menuFileName, int windowWidth, int windowHeight);
	virtual ~HUD();

	virtual void	update(sf::Time& elapsedTime, bool ability1Ready, bool ability2Ready, int hull, int score);
	void			SetAbilities(int selection, int hull);

	bool			m_gameStarted;

private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int				m_windowWidth;
	int				m_windowHeight;

	sf::Vector2f	textpos;

	sf::Font		m_font;
	sf::Color		m_hudTextColour;
	sf::Color		m_textColour;
	sf::Color		m_textOutline;

	sf::Texture		m_blinkTexture;
	sf::Sprite		m_blinkSprite;

	sf::Texture		m_rapidFireTexture;
	sf::Sprite		m_rapidFireSprite;

	sf::Texture		m_shieldTexture;
	sf::Sprite		m_shieldSprite;

	sf::Texture		m_mineTexture;
	sf::Sprite		m_mineSprite;

	sf::Texture		m_tractorBeamTexture;
	sf::Sprite		m_tractorBeamSprite;

	sf::Texture		m_ramTexture;
	sf::Sprite		m_ramSprite;

	sf::Text		m_blinkTitle;
	sf::Text		m_rapidFireTitle;
	sf::Text		m_shieldTitle;
	sf::Text		m_mineTitle;
	sf::Text		m_tractorBeamTitle;
	sf::Text		m_ramTitle;
	sf::Text		m_hull;
	sf::Text		m_score;

	sf::Sprite		m_ability1Sprite;
	sf::Sprite		m_ability2Sprite;

	sf::Text		m_ability1Text;
	sf::Text		m_ability2Text;

	sf::FloatRect	textbox;
};

#endif