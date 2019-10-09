#include "Camera.h"

Camera::Camera(int& projectionWindowWidth, int& projectionWindowHeight)
	: m_cameraPosition(0, 0)
	, m_cameraWindowSize(projectionWindowWidth, projectionWindowHeight)
	, m_cameraZoom(0.5)
{
}

Camera::~Camera()
{
}

void Camera::setPosition(sf::Vector2f target)
{
	//Set camera position to input
	m_cameraPosition = target;
}

sf::FloatRect Camera::getCameraWindow(float& parallaxFactor)
{
	sf::FloatRect window;

	//calculates the top left coordinate of visible area
	window.left = m_cameraPosition.x - m_cameraWindowSize.x / 2 * m_cameraZoom * parallaxFactor;
	window.top = m_cameraPosition.y - m_cameraWindowSize.y / 2 * m_cameraZoom * parallaxFactor;

	//width and height are x and y attributes
	window.width = m_cameraWindowSize.x * m_cameraZoom * parallaxFactor;
	window.height = m_cameraWindowSize.y * m_cameraZoom * parallaxFactor;

	//return rectangle
	return window;
}

sf::Transform Camera::getViewTransform() const
{
	//Transform coordinate from WORLD space to CAMERA space
	//Centered at middle of visible window
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraPosition);
	return transform.getInverse();
}

sf::Transform Camera::getProjTransform() const
{
	//Trasform coordinate from CAMERA space to SCREEN space
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraWindowSize.x / 2, m_cameraWindowSize.y / 2);
	transform.scale(0.4f / m_cameraZoom, 0.4f / m_cameraZoom);
	return transform;
}