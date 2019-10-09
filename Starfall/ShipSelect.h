#ifndef SHIPSELECT
#define SHIPSELECT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ShipSelect :
	public sf::Drawable, public sf::Transformable
{
public:
	ShipSelect(std::string menuFileName, int& windowWidth, int& windowHeight);
	~ShipSelect();

	int						update(sf::Time& elapsedTime);

private:

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void					hideGnat();
	void					showGnat();
	void					hideMantis();
	void					showMantis();
	void					hideTug();
	void					showTug();

	bool					m_prevDownKeyPressed;
	bool					m_prevUpKeyPressed;
	bool					m_prevReturnKeyPressed;
	int						m_highlightIndex;
	int						m_selection;

	sf::Texture				m_backgroundTexture;
	sf::Sprite				m_backgroundSprite;
	sf::FloatRect			m_backgroundRect;

	sf::Texture				m_containerTexture;
	sf::Sprite				m_containerSprite;

	sf::Texture				m_gnatTexture;
	sf::Sprite				m_gnatSprite;

	sf::Texture				m_mantisTexture;
	sf::Sprite				m_mantisSprite;

	sf::Texture				m_tugTexture;
	sf::Sprite				m_tugSprite;

	sf::Texture				m_blinkTexture;
	sf::Sprite				m_blinkSprite;

	sf::Texture				m_rapidFireTexture;
	sf::Sprite				m_rapidFireSprite;

	sf::Texture				m_shieldTexture;
	sf::Sprite				m_shieldSprite;

	sf::Texture				m_mineTexture;
	sf::Sprite				m_mineSprite;

	sf::Texture				m_tractorBeamTexture;
	sf::Sprite				m_tractorBeamSprite;

	sf::Texture				m_ramTexture;
	sf::Sprite				m_ramSprite;

	sf::Texture				m_comingSoonTexture;
	sf::Sprite				m_comingSoonSprite;

	sf::Font				m_gameFont;
	sf::Color				m_highlightTextColour;
	sf::Color				m_normalTextColour;
	sf::Color				m_normalOutlineColour;
	sf::Color				m_highlightOutlineColour;

	sf::Vector2f			m_menuItemBorder;
	std::vector<sf::Text>	m_menuText;

	sf::Text				m_gnatTitle;
	sf::Text				m_mantisTitle;
	sf::Text				m_tugTitle;

	sf::Text				m_gnatHull;
	sf::Text				m_gnatSpeed;
	sf::Text				m_mantisHull;
	sf::Text				m_mantisSpeed;
	sf::Text				m_tugHull;
	sf::Text				m_tugSpeed;

	sf::Text				m_blinkTitle;
	sf::Text				m_rapidFireTitle;

	sf::Text				m_shieldTitle;
	sf::Text				m_mineTitle;

	sf::Text				m_tractorBeamTitle;
	sf::Text				m_ramTitle;

	sf::Text				m_blinkText;
	sf::Text				m_rapidFireText;

	sf::Text				m_shieldText;
	sf::Text				m_mineText;

	sf::Text				m_tractorBeamText;
	sf::Text				m_ramText;

	sf::Vector2f			textpos;

	enum MENU_ALIGNMENT
	{
		LEFT_JUSTIFIED,
		CENTRE_JUSTIFIED,
		RIGHT_JUSTIFIED
	};

	MENU_ALIGNMENT			m_menuAlignment;
};

#endif
