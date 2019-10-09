#include "Bullet.h"

Bullet::Bullet()
	: m_distanceTravelled(0)
	, m_active(true)
{
}

Bullet::~Bullet()
{
}

void Bullet::setSpeed(float speed)
{
	m_moveSpeed = speed;
}

void Bullet::setMoveDirection(sf::Vector2f directionVector, bool rotate)
{
	//Sets bullet movement direction
	m_moveDirection = directionVector;

	if (rotate)
	{
		float angleRadian = atan2(directionVector.y, directionVector.x);
		float angleDegree = angleRadian / PI * 180;
		setRotation(angleDegree);
	}
}

void Bullet::setMaxRange(float range)
{
	m_maxRange = range;
}

void Bullet::setActive()
{
	m_active = true;
}

void Bullet::update(sf::Time& elapsedTime)
{
	if (m_active)
	{
		move(m_moveDirection * m_moveSpeed * elapsedTime.asSeconds());
		m_distanceTravelled += m_moveSpeed * elapsedTime.asSeconds();

		if (m_distanceTravelled >= m_maxRange)
			m_active = false;
	}

	SpriteObject::update(elapsedTime);
}

bool Bullet::isActive()
{
	return m_active;
}

void Bullet::applyTexture(sf::Texture* texture)
{
	m_initialised = true;
	m_spriteTexture = texture;
	// Setting default origin and rectangle

	m_spriteOrigin = sf::Vector2f(m_spriteTexture->getSize().x / 2, m_spriteTexture->getSize().y / 2);
	m_textureRectangle = sf::IntRect(0, 0, m_spriteTexture->getSize().x, m_spriteTexture->getSize().y);
}
