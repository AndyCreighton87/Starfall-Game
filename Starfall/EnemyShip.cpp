#include "EnemyShip.h"

EnemyShip::EnemyShip()
	: m_targetLocation(0, 0)
	, m_moveSpeed(200.0f)
	, m_readyToShoot(true)
	, m_timeSinceLastShoot(0)
	, m_bulletIsShot(false)
	, m_caughtInTractorBeam(false)
{
	m_navArrow = new SpriteObject();
	m_navArrow->setDefaultTexture("Media/Textures/navarrow.png");
	//m_navArrow->setColour(sf::Color(255, 255, 255, 0));
}

EnemyShip::~EnemyShip()
{
	
}

Bullet* EnemyShip::processEvents(sf::Time& elapsedTime, sf::Vector2f playerShipPosition)
{
	Bullet* bullet = NULL;

	//Get NPCs current location
	sf::Vector2f currentPosition = getPosition();

	//Calculate vector from NPCs current position to target point
	sf::Vector2f faceDirection = m_targetLocation - currentPosition;

	float angle = atan2(faceDirection.y, faceDirection.x);
	setRotation(angle / PI * 180);

	//If the player ship is within range, the enemy ship will stop and shoot. If not it will move
	//towards player ships location
	if (playerShipInRange(currentPosition, playerShipPosition))
	{
		bullet = shoot(elapsedTime);
	}
	else
	{
		sf::Vector2f unitMoveVector = sf::Vector2f(cos(angle), sin(angle));
		sf::Vector2f totalMoveVector = unitMoveVector * elapsedTime.asSeconds() * m_moveSpeed;
		move(totalMoveVector);
	}

	//Manages enemy ship firing speed
	if (m_timeSinceLastShoot > 2)
	{
		m_readyToShoot = true;
		m_timeSinceLastShoot = 0;
	}
	else
	{
		m_timeSinceLastShoot += elapsedTime.asSeconds();
		m_readyToShoot = false;
	}

	m_faceAngle = getRotation();

	return bullet;
}

void EnemyShip::setTargetLocation(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

void EnemyShip::setMovementSpeed(float speed)
{
	m_moveSpeed = speed;
}

void EnemyShip::manageNavArrow(sf::Vector2f playerPosition, sf::Time elapsedTime)
{
	//Function that manages nav arrows that show where enemies are

	sf::Vector2f enemyPosition = this->getPosition();

	float radius = 500.0f;

	sf::Vector2f dist = enemyPosition - playerPosition;

	//Checks the range of enemyShips, if they are within a radius of 800 the nav arrow will no longer
	//be visable. If they are outside of that range the nav arrow will be visable and point towards the
	//enemyShip with correct positioning and rotation around the player.
	if (m_Maths->L2Norm(dist) > 800.0f)
	{
		sf::Vector2f dir = m_Maths->Normalise(dist);

		m_navArrow->setColour(sf::Color(255, 255, 255, 255));
		m_navArrow->setPosition(playerPosition.x + (dir.x * radius), playerPosition.y + (dir.y * radius));
		m_navArrow->setRotation(this->getFacing() + 180);
	}
	else
	{
		m_navArrow->setColour(sf::Color(255, 255, 255, 0));
	}

	m_navArrow->update(elapsedTime);
}

float EnemyShip::getFacing()
{
	//Gets direction of facing in degrees
	return m_faceAngle;
}

bool EnemyShip::playerShipInRange(sf::Vector2f currentPosition, sf::Vector2f playerShipPosition)
{
	//Function to check if player is within range of a predefined radius

	//get enemyShip current location
	sf::Vector2f vector = playerShipPosition - currentPosition;

	float radius = 570;

	//Calculate distance between playerShip and enemyShip (L2 norm)
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);

	if (distance < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Bullet* EnemyShip::shoot(sf::Time& elapsedTime)
{
	//Create new bullet object
	if (m_readyToShoot)
	{
		Bullet*	bullet = new Bullet();

		bullet->setDefaultTexture("Media/Textures/enemybullet.png");
		bullet->setPosition(getWorldPosition());
		bullet->setMaxRange(3000);
		bullet->setSpeed(1000);

		float angle = getRotation() / 180 * PI;
		sf::Vector2f faceDirection = sf::Vector2f(cos(angle), sin(angle));
		bullet->setMoveDirection(faceDirection, true);

		m_timeSinceLastShoot = 0;
		m_readyToShoot = false;

		m_bulletIsShot = true;

		//Creates a new bullet shot animation
		EffectsAnimations* shootfx = new EffectsAnimations("Media/Textures/Animations/enemyshootfx.png", "Media/SpriteInfo/shootfx.txt", 1.0f);
		shootfx->setPosition(m_Maths->parametricCircle(this->getFacing() * PI / 180, this->getLocalBounds().width / 1.5, this->getPosition()));
		shootfx->setRotation(this->getFacing());
		m_enemyShipEffects.push_back(shootfx);

		return bullet;
	}
	else
	{
		return NULL;
	}
}

void EnemyShip::update(sf::Time& elapsedTime)
{
	//Update enemy ship effects
	for (int i = 0; i < m_enemyShipEffects.size(); ++i)
	{
		if (m_enemyShipEffects[i]->m_destroyAnimation)
		{
			m_enemyShipEffects.erase(std::remove(m_enemyShipEffects.begin(), m_enemyShipEffects.end(), m_enemyShipEffects[i]));
		}
		else
		{
			m_enemyShipEffects[i]->update(elapsedTime);
		}
	}

	//Update nav arrows
	manageNavArrow(m_targetLocation, elapsedTime);

	SpriteObject::update(elapsedTime);
}