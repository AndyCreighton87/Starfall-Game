#ifndef ENEMYSHIP
#define ENEMYSHIP

#include "AnimatedSpriteObject.h"
#include "Bullet.h"
#include "EffectsAnimations.h"
#include "Maths.h"

class EnemyShip :
	public SpriteObject
{
public:
	EnemyShip();
	virtual ~EnemyShip();

	virtual void			update(sf::Time& elapsedTime);
	void					setTargetLocation(sf::Vector2f targetLocation);
	void					setMovementSpeed(float speed);
	void					manageNavArrow(sf::Vector2f playerPosition, sf::Time elapsedTime);
	bool					playerShipInRange(sf::Vector2f currentPosition, sf::Vector2f playerShipPosition);
	float					getFacing();

	Bullet*					processEvents(sf::Time& elapsedTime, sf::Vector2f playerShipPosition);
	
	SpriteObject*			m_navArrow;

	bool					m_bulletIsShot;
	bool					m_caughtInTractorBeam;
	float					m_moveSpeed;

	std::vector<EffectsAnimations*>	m_enemyShipEffects;

private:
	Bullet*					shoot(sf::Time& elapsedTime);
	Maths*					m_Maths;

	bool					m_readyToShoot;
	float					m_timeSinceLastShoot;
	float					m_faceAngle;

	sf::Vector2f			m_targetLocation;
};

#endif