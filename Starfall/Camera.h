#ifndef CAMERA
#define CAMERA

#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(int& projectionWindowWidth, int& projectionWindowHeight);
	~Camera();

	sf::FloatRect		getCameraWindow(float& parallaxFactor);

	void				setPosition(sf::Vector2f target);

	sf::Transform		getViewTransform() const;
	sf::Transform		getProjTransform() const;

private:
	sf::Vector2f		m_cameraWindowSize;
	sf::Vector2f		m_cameraPosition;

	float				m_cameraZoom;
};

#endif
