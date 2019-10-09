#include "PlayerShip.h"

PlayerShip::PlayerShip()
	: m_rangeWeaponCooldown(0)
	, m_timeSinceLastShoot(0)
	, m_moveSpeed(1000)
	, m_readyToShoot(true)
	, m_bulletIsShot(false)
	, m_firingSpeed(300)
	, m_rapidFireActive(false)
	, m_usingAbility(false)
	, m_shieldActive(false)
	, m_tractorBeamActive(false)
	, m_ability1Ready(true)
	, m_ability2Ready(true)
{
	//Timers for abilties
	m_rapidFireElapsed = sf::Time::Zero;
	m_rapidFireTimer = sf::seconds(5);

	m_tractorBeamElapsed = sf::Time::Zero;
	m_tractorBeamTimer = sf::seconds(7);

	m_ability1Elapsed = sf::Time::Zero;
	m_ability2Elapsed = sf::Time::Zero;
	m_abilityCooldown = sf::seconds(10);

	m_shield = new SpriteObject();
	m_shield->setDefaultTexture("Media/Textures/shield.png");
	m_shield->setColour(sf::Color(255, 255, 255, 0));
}

PlayerShip::~PlayerShip()
{

}

Bullet* PlayerShip::processEvents(sf::Time& elapsedTime, sf::Transform transform, sf::Vector2f mouseScreenPosition)
{
	Bullet* bullet = NULL;

	// check mouse buttons state
	bool leftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool rightButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	m_transform = transform;

	// get character screen position
	sf::Vector2f charScreenPos = getScreenPosition(transform);

	// calculate vector difference
	sf::Vector2f differenceVector = mouseScreenPosition - charScreenPos;

	// calculate angle between the vector and the horizontal +ve x axis
	// horizontal positive x-axis is defined 0 degree, sprite facing right initially
	double angleinRadians = atan2(differenceVector.y, differenceVector.x);
	double angleinDegrees = angleinRadians / PI * 180;

	// calculate the magnitude of the difference vector
	double magnitude = sqrt(differenceVector.x*differenceVector.x + differenceVector.y*differenceVector.y);

	// normalise the difference vector
	differenceVector.x /= magnitude;
	differenceVector.y /= magnitude;

	//Shoot
	if (leftButtonPressed)
	{
		if (!m_usingAbility)
			bullet = shoot(elapsedTime);
	}

	m_faceAngle = getRotation();

	//Manage movement based on keyboard input
	float moveSpeed;
	sf::Vector2f moveDirection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		float moveAngle = m_faceAngle - 90;
		moveAngle = moveAngle / 180 * PI;
		float cosine = cos(moveAngle);
		float sine = sin(moveAngle);

		moveSpeed = m_moveSpeed;
		moveDirection.x = cosine;
		moveDirection.y = sine;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		float moveAngle = m_faceAngle + 90;
		moveAngle = moveAngle / 180 * PI;
		float cosine = cos(moveAngle);
		float sine = sin(moveAngle);

		moveSpeed = m_moveSpeed;
		moveDirection.x = cosine;
		moveDirection.y = sine;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		float moveAngle = m_faceAngle;
		moveAngle = moveAngle / 180 * PI;
		float cosine = cos(moveAngle);
		float sine = sin(moveAngle);

		moveSpeed = m_moveSpeed;
		moveDirection.x = cosine;
		moveDirection.y = sine;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		float moveAngle = m_faceAngle + 180;
		moveAngle = moveAngle / 180 * PI;
		float cosine = cos(moveAngle);
		float sine = sin(moveAngle);

		moveSpeed = m_moveSpeed;
		moveDirection.x = cosine;
		moveDirection.y = sine;
	}
	else
	{
		moveSpeed = 0;
	}

	setRotation(angleinDegrees);

	move(moveDirection*moveSpeed*elapsedTime.asSeconds());

	//Firing speed
	if (m_timeSinceLastShoot > m_firingSpeed)
	{
		m_readyToShoot = true;
		m_timeSinceLastShoot = 0;
	}
	else
	{
		m_timeSinceLastShoot += elapsedTime.asMilliseconds();
		m_readyToShoot = false;
	}

	return bullet;
}

Bullet* PlayerShip::shoot(sf::Time elapsedTime)
{
	
	if (m_readyToShoot)
	{
		//Creates a new bullet object
		Bullet*	bullet = new Bullet();

		bullet->setDefaultTexture("Media/Textures/bullet.png");
		bullet->setPosition(getWorldPosition());
		bullet->setMaxRange(3000);
		bullet->setSpeed(2000);

		float angle = getRotation() / 180 * PI;
		sf::Vector2f faceDirection = sf::Vector2f(cos(angle), sin(angle));
		bullet->setMoveDirection(faceDirection, true);

		m_timeSinceLastShoot = 0;
		m_readyToShoot = false;
		m_bulletIsShot = true;

		//Creates a bullet shot effect
		EffectsAnimations* shootfx = new EffectsAnimations("Media/Textures/Animations/shootfx.png", "Media/SpriteInfo/shootfx.txt", 1.0f);
		shootfx->setPosition(m_Maths->parametricCircle(this->getFacing() * PI / 180, this->getLocalBounds().width / 1.5, this->getPosition()));
		shootfx->setRotation(this->getFacing());
		m_playerShipEffects.push_back(shootfx);

		return bullet;
	}
	else
	{
		return NULL;
	}
}

void PlayerShip::manageAbilities(sf::Time elapsedTime)
{
	m_ability1Elapsed += elapsedTime;
	m_ability2Elapsed += elapsedTime;

	if (!m_ability1Ready)
	{
		if (m_ability1Elapsed > m_abilityCooldown)
		{
			m_ability1Ready = true;
		}
	}

	if (!m_ability2Ready)
	{
		if (m_ability2Elapsed > m_abilityCooldown)
		{
			m_ability2Ready = true;
		}
	}

	bool qButtonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	bool eButtonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

	switch (m_selection)
	{
		//Gnat
	case 0:
		if (qButtonPressed && m_ability1Ready)
		{
			//Blink
			sf::Vector2f position = (blink(this->getPosition()));
			this->setPosition(position);
			m_ability1Ready = false;
			m_ability1Elapsed = sf::Time::Zero;
		}

		if (eButtonPressed && m_ability2Ready)
		{
			//Rapid Fire
			this->rapidFire();
			m_ability2Ready = false;
			m_ability2Elapsed = sf::Time::Zero;
		}
		break;

		//Mantis
	case 1:
		if (qButtonPressed)
		{
			//Shield
			m_shield->setColour(sf::Color(255, 255, 255, 255));
			m_shield->setPosition(this->getPosition());
			m_shield->update(elapsedTime);
			m_shieldActive = true;
			m_usingAbility = true;
		}
		else
		{
			m_shield->setColour(sf::Color(255, 255, 255, 0));
			m_usingAbility = false;
			m_shieldActive = false;
		}

		if (eButtonPressed && m_ability2Ready)
		{
			//Mine
			m_mineList.push_back(mine(this->getPosition()));
			m_ability2Ready = false;
			m_ability2Elapsed = sf::Time::Zero;
		}
		break;

		//Tug
	case 2:
		if (qButtonPressed && m_ability1Ready)
		{
			//Tractor Beam
			m_tractorBeam = tractorBeam();
			m_usingAbility = true;
			m_ability1Ready = false;
			m_ability1Elapsed = sf::Time::Zero;
		}

		if (eButtonPressed && m_ability2Ready)
		{
			//Ram
			m_ability2Ready = false;
			m_ability2Elapsed = sf::Time::Zero;
		}
		break;

	default:
		break;

	}
}

float PlayerShip::getFacing()
{
	//Gets direction of facing in degrees
	return m_faceAngle;
}

void PlayerShip::setSpeed(float speed)
{
	//Sets movement speed
	m_moveSpeed = speed;
}

void PlayerShip::shipChoice(int selection)
{
	m_selection = selection;
	switch (selection)
	{
	case 0:
		this->setDefaultTexture("Media/Textures/gnat.png");
		m_hull = 80;
		this->setSpeed(600);
		break;

	case 1:
		this->setDefaultTexture("Media/Textures/mantis.png");
		m_hull = 100;
		this->setSpeed(500);
		break;

	case 2:
		this->setDefaultTexture("Media/Textures/tug.png");
		m_hull = 120;
		this->setSpeed(400);
		break;

	default:
		this->setDefaultTexture("Media/Textures/mantis.png");
		m_hull = 100;
		this->setSpeed(500);
		break;
	}
}

sf::Vector2f PlayerShip::blink(sf::Vector2f position)
{
	//Sets and returns the position of the blink ability
	sf::Vector2f blinkLocation(m_Maths->parametricCircle(m_faceAngle * PI / 180, 600.0f, position));

	EffectsAnimations* blinkAnimation = new EffectsAnimations("Media/Textures/Animations/blinkanimation.png", "Media/SpriteInfo/blink.txt", 1.0f);
	blinkAnimation->setPosition(blinkLocation);
	m_playerShipEffects.push_back(blinkAnimation);

	return blinkLocation;
}

void PlayerShip::rapidFire()
{
	//Activites Rapid Fire
	m_rapidFireActive = true;
}

SpriteObject* PlayerShip::mine(sf::Vector2f playerPosition)
{
	//Creates a new mine object
	SpriteObject* mine = new SpriteObject();

	mine->setDefaultTexture("Media/Textures/mine.png");
	mine->setPosition(playerPosition);

	return mine;
}

SpriteObject* PlayerShip::tractorBeam()
{
	//Creates a new Tractor Beam object
	m_tractorBeam = new SpriteObject();
	m_tractorBeam->setDefaultTexture("Media/Textures/tractorbeam.png");
	m_tractorBeamActive = true;
	m_usingAbility = true;

	return m_tractorBeam;
}

void PlayerShip::update(sf::Time& elapsedTime)
{
	manageAbilities(elapsedTime);

	//Checks if rapid fire is active, if it is - increase firing speed
	if (m_rapidFireActive == true)
	{
		m_rapidFireElapsed += elapsedTime;
		m_firingSpeed = 125;

		if (m_rapidFireElapsed > m_rapidFireTimer)
		{
			m_rapidFireActive = false;
			m_firingSpeed = 300;
			m_rapidFireElapsed = sf::Time::Zero;
		}
	}

	//Updates Tractor Beam
	if (m_tractorBeamActive == true)
	{
		m_tractorBeamElapsed += elapsedTime;

		sf::Vector2f origin = this->getPosition();

		m_tractorBeam->setPosition(m_Maths->parametricCircle(this->getFacing() * PI / 180, this->getLocalBounds().width * 1.8, this->getPosition()));
		m_tractorBeam->setRotation(this->getFacing());

		if (m_tractorBeamElapsed > m_tractorBeamTimer)
		{
			m_tractorBeam = NULL;
			m_tractorBeamActive = false;
			m_tractorBeamElapsed = sf::Time::Zero;
		}
	}

	//Updates all effects
	for (int i = 0; i < m_playerShipEffects.size(); ++i)
	{
		if (m_playerShipEffects[i]->m_destroyAnimation)
		{
			m_playerShipEffects.erase(std::remove(m_playerShipEffects.begin(), m_playerShipEffects.end(), m_playerShipEffects[i]));
		}
		else
		{
			m_playerShipEffects[i]->update(elapsedTime);
		}
	}

	SpriteObject::update(elapsedTime);
}