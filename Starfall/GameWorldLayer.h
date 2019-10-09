#ifndef GAMEWORLDLAYER
#define GAMEWORLDLAYER

#include <SFML/Graphics.hpp>
#include "Camera.h"

class GameWorldLayer :
	public sf::Drawable, public sf::Transformable
{
public:
	GameWorldLayer(std::string textureFileName, float parallaxFactor, int& viewportWidth, int& viewportHeight, sf::Vector2f scrollSpeed);
	~GameWorldLayer();

	void			update(sf::Time elapsedTime);
	void			followCamera(Camera* camera);
	void			setParallaxFactor(float parallaxFactor);
	float			getParallaxFactor();

private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float			m_parallaxFactor;

	sf::Texture		m_layerTexture;
	sf::VertexArray m_layerVerticies;

	sf::Vector2f	m_offset;
	sf::Vector2f	m_scrollSpeed;
};

#endif