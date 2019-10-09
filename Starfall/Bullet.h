#ifndef BULLET
#define BULLET

#include "SpriteObject.h"

class Bullet :
	public SpriteObject
{
public:
	Bullet();
	virtual ~Bullet();

	virtual void		update(sf::Time& elapsedTime);
	void				setActive();
	void				setMaxRange(float range);
	void				setSpeed(float speed);
	void				setMoveDirection(sf::Vector2f directionVector, bool rotate);
	void				applyTexture(sf::Texture* texture);
	bool				isActive();

private:
	bool				m_active;
	bool				m_initialised;
	float				m_maxRange;
	float				m_distanceTravelled;
	float				m_moveSpeed;

	sf::Vector2f		m_moveDirection;
};
#endif
