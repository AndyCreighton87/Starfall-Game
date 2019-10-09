#include "GameWorldLayer.h"

GameWorldLayer::GameWorldLayer(std::string textureFileName, float parallaxFactor, int& viewportWidth, int& viewportHeight, sf::Vector2f scrollSpeed)
	: m_layerTexture()
	, m_layerVerticies(sf::Quads, 4)
	, m_parallaxFactor(parallaxFactor)
{
	if (m_layerTexture.loadFromFile(textureFileName))
	{
		//set texture
		m_layerTexture.setRepeated(true);

		//set verticies of the quad
		m_layerVerticies[0].position = sf::Vector2f(0.f, 0.f);
		m_layerVerticies[1].position = sf::Vector2f(0.f, viewportHeight);
		m_layerVerticies[2].position = sf::Vector2f(viewportWidth, viewportHeight);
		m_layerVerticies[3].position = sf::Vector2f(viewportWidth, 0.f);

		m_scrollSpeed = scrollSpeed;
	}
}

GameWorldLayer::~GameWorldLayer()
{

}

void GameWorldLayer::followCamera(Camera* camera)
{
	//find visible area of camera
	sf::FloatRect cameraWindows = camera->getCameraWindow(m_parallaxFactor);

	//calculate left, right, top and bottom values
	int left = cameraWindows.left + m_offset.x;
	int right = cameraWindows.left + cameraWindows.width + m_offset.x;
	int top = cameraWindows.top + m_offset.y;
	int bottom = cameraWindows.top + cameraWindows.height + m_offset.y;

	//set texture cordinates
	m_layerVerticies[0].texCoords = sf::Vector2f(left, top);
	m_layerVerticies[1].texCoords = sf::Vector2f(left, bottom);
	m_layerVerticies[2].texCoords = sf::Vector2f(right, bottom);
	m_layerVerticies[3].texCoords = sf::Vector2f(right, top);
}

void GameWorldLayer::setParallaxFactor(float parallaxFactor)
{
	m_parallaxFactor = parallaxFactor;
}

float GameWorldLayer::getParallaxFactor()
{
	return m_parallaxFactor;
}

void GameWorldLayer::update(sf::Time elapsedTime)
{
	m_offset = m_offset + elapsedTime.asSeconds() * m_scrollSpeed;
}

void GameWorldLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//assign m_layertexture to renderstate
	states.texture = &m_layerTexture;

	//Draw quad
	target.draw(m_layerVerticies, states);
}