#ifndef PLAYERSHIP
#define PLAYERSHIP

#include "AnimatedSpriteObject.h"
#include "Bullet.h"
#include "EffectsAnimations.h"

class PlayerShip :
	public SpriteObject
{
public:
	PlayerShip();
	virtual ~PlayerShip();

	Bullet*					processEvents(sf::Time& elapsedTime, sf::Transform transform, sf::Vector2f mouseScreenPosition);

	sf::Vector2f			blink(sf::Vector2f position);
	void					rapidFire();
	SpriteObject*			mine(sf::Vector2f playerPosition);
	SpriteObject*			tractorBeam();
	
	virtual void			update(sf::Time& elapsedTime);
	void					setSpeed(float speed);
	void					shipChoice(int selection);
	float					getFacing();

	sf::Texture				bulletTexture;
	SpriteObject*			m_tractorBeam;
	SpriteObject*			m_shield;

	bool					m_bulletIsShot;
	bool					m_usingAbility;
	bool					m_rapidFireActive;
	bool					m_shieldActive;
	bool					m_tractorBeamActive;
	bool					m_ability1Ready;
	bool					m_ability2Ready;

	float					m_moveSpeed;

	int						m_hull;
	int						m_selection;

	std::vector<SpriteObject*>		m_mineList;
	std::vector<EffectsAnimations*>	m_playerShipEffects;

private:
	Bullet*					shoot(sf::Time elapsedTime);
	void					manageAbilities(sf::Time elapsedTime);
	
	Maths*					m_Maths;

	bool					m_readyToShoot;
	float					m_rangeWeaponCooldown;
	float					m_timeSinceLastShoot;
	float					m_firingSpeed;

	sf::Vector2f			m_mouseScreenPos;
	sf::Transform			m_transform;
	
	sf::Vector2f			m_faceDirection;
	sf::Texture				m_bulletTexture;

	sf::Vector2f			m_tractorBeamPosition;

	sf::Time				m_rapidFireElapsed;
	sf::Time				m_rapidFireTimer;

	sf::Time				m_tractorBeamElapsed;
	sf::Time				m_tractorBeamTimer;

	sf::Time			m_ability1Elapsed;
	sf::Time			m_ability2Elapsed;
	sf::Time			m_abilityCooldown;
	sf::Time			m_rapidFireDuration;
	sf::Time			m_tractorBeamDuration;

	

protected:
	float					m_faceAngle;
};

#endif
