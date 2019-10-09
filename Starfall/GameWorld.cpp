#include "GameWorld.h"

GameWorld::GameWorld(int& windowWidth, int& windowHeight, sf::RenderWindow* parentWindow)
	: m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_camera(windowWidth, windowHeight)
	, m_enemiesKilled(0)
	, m_numberOfEnemies(5)
	, m_ability1Ready(true)
	, m_ability2Ready(true)
	, m_HUD("Media/MenuInfo/hud.txt", windowWidth, windowHeight)
{
	//Load and sort Game Layers
	GameWorldLayer* background = new GameWorldLayer("Media/Textures/space.jpg", 1.0f, windowWidth, windowHeight, sf::Vector2f(0, 0));
	m_gameWorldLayerList.push_back(background);

	GameWorldLayer* asteroids = new GameWorldLayer("Media/Textures/asteroids.png", 0.8f, windowWidth, windowHeight, sf::Vector2f(0, 0));
	m_gameWorldLayerList.push_back(asteroids);

	GameWorldLayer* gasclouds = new GameWorldLayer("Media/Textures/gasclouds.png", 0.7f, windowWidth, windowHeight, sf::Vector2f(0, 0));
	m_gameWorldLayerList.push_back(gasclouds);

	std::sort(m_gameWorldLayerList.begin(), m_gameWorldLayerList.end(), layerSort);
	
	//set cameras initial position
	m_cameraPosition = sf::Vector2f(0, 0);
	m_parentWindow = parentWindow;

	//Set random seed to time
	srand(time(0));

	//create player ship
	m_playerShip = new PlayerShip();
	m_playerShip->setPosition(0, 0);
	m_playerShip->setOrigin(m_playerShip->getGlobalBounds().width / 2, m_playerShip->getGlobalBounds().height / 2);
	m_staticObjectList.push_back(m_playerShip);

	//Create next wave text
	m_waveSprite = new SpriteObject;
	m_waveSprite->setDefaultTexture("Media/Textures/nextwave.png");
	m_waveSprite->setColour(sf::Color(255, 255, 255, 0));
	m_staticObjectList.push_back(m_waveSprite);

	//Set font
	m_gameFont.loadFromFile("Media/Fonts/gameover.ttf");
	m_textColour = sf::Color(255, 255, 255, 255);
	m_outlineColour = sf::Color(0, 0, 0, 255);
	m_textHide = sf::Color(255, 255, 255, 0);
	m_outlineHide = sf::Color(0, 0, 0, 0);

	//Set timers
	m_waveElapsed = sf::Time::Zero;
	m_waveTimer = sf::seconds(3);

	//create enemies
	spawnEnemies();
}

GameWorld::~GameWorld()
{
	//Clear game world layer
	for (std::vector<GameWorldLayer*>::iterator it = m_gameWorldLayerList.begin(); it != m_gameWorldLayerList.end(); ++it)
	{
		delete(*it);
	}
	m_gameWorldLayerList.clear();

	//Clear bullet list
	for (std::vector<Bullet*>::iterator it = m_bulletList.begin(); it != m_bulletList.end(); ++it)
	{
		delete(*it);
	}
	m_bulletList.clear();

	//Clear bullet list
	for (std::vector<Bullet*>::iterator it = m_enemyBulletList.begin(); it != m_enemyBulletList.end(); ++it)
	{
		delete(*it);
	}
	m_enemyBulletList.clear();

	//Clear the static object
	for (std::vector<SpriteObject*>::iterator it = m_staticObjectList.begin(); it != m_staticObjectList.end(); ++it)
	{
		delete (*it);
	}
	m_staticObjectList.clear();

	//Clear enemy ship list
	for (std::vector<EnemyShip*>::iterator it = m_enemyShipList.begin(); it != m_enemyShipList.end(); ++it)
	{
		delete (*it);
	}
	m_enemyShipList.clear();
}

void GameWorld::processEvents(sf::Time& elapsedTime)
{
	//Loads the ship selection into the HUD, loading the appropriate abilities 
	if (m_HUD.m_gameStarted == false)
	{
		m_HUD.SetAbilities(m_playerShip->m_selection, m_playerShip->m_hull);
		m_HUD.m_gameStarted = true;
	}

	//get camera transform (world -> screen)
	sf::Transform transform;
	transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	sf::Transform inv = transform.getInverse();

	//Get mouse position
	sf::Vector2f mouseScreenPosition = sf::Vector2f(sf::Mouse::getPosition(*m_parentWindow));

	//Convert to world space coordinate
	sf::Vector2f wp = m_playerShip->getPosition();

	//Create bullet object
	Bullet* bullet = m_playerShip->processEvents(elapsedTime, transform, mouseScreenPosition);
	if (bullet)
	{
		m_bulletList.push_back(bullet);
	}
	
	//Create enemy bullets
	for (auto c = m_enemyShipList.begin(); c != m_enemyShipList.end();)
	{
		Bullet* enemyBullet = (*c)->processEvents(elapsedTime, m_playerShip->getPosition());
		if (enemyBullet)
			m_enemyBulletList.push_back(enemyBullet);

		++c;
	}

	//Load next wave and spawn enemies
	if (m_enemiesKilled >= m_numberOfEnemies)
	{
		m_waveElapsed += elapsedTime;

		if (m_waveElapsed > m_waveTimer)
		{
			m_waveIsShown = !m_waveIsShown;
			m_waveElapsed -= m_waveTimer;
			if (m_waveIsShown)
			{
				//Shows next wave text
				m_waveSprite->setColour(sf::Color(255, 255, 255, 255));
			}
			else
			{
				//Hides next wave text
				m_waveSprite->setColour(sf::Color(255, 255, 255, 0));
				m_enemiesKilled = 0;

				//Increases number of enemies by 1 and increases movement speed
				++m_numberOfEnemies;
				spawnEnemies();
				for (auto c : m_enemyShipList)
					c->setMovementSpeed(c->m_moveSpeed + 20);
			}
		}
	}

	//Checks all collision within the gameworld
	collisionChecks(elapsedTime);
}

bool GameWorld::layerSort(GameWorldLayer* a, GameWorldLayer* b)
{
	//Function that sorts the gameworld layers based upon their
	//parallax factor

	return (a->getParallaxFactor() > b->getParallaxFactor());
}

void GameWorld::update(sf::Time& elapsedTime)
{
	processEvents(elapsedTime);

	//Update static sprite objects
	for (auto c : m_staticObjectList)
	{
		c->update(elapsedTime);
	}

	//Update each Game World Layer
	for (auto c : m_gameWorldLayerList)
	{
		c->followCamera(&m_camera);
		c->update(elapsedTime);
	}

	//Update enemy ships
	for (auto c : m_enemyShipList)
	{
		c->setTargetLocation(m_playerShip->getPosition());
		c->update(elapsedTime);
	}

	//Updating all bullets
	for (auto b = m_bulletList.begin(); b != m_bulletList.end();)
	{
		if ((*b)->isActive())
		{
			(*b)->update(elapsedTime);
			++b;
		}
		else if ((*b)->isActive() == false)
		{
			b = m_bulletList.erase(b);
		}
	}

	//Update all enemy bullets
	for (auto b = m_enemyBulletList.begin(); b != m_enemyBulletList.end();)
	{
		if ((*b)->isActive())
		{
			(*b)->update(elapsedTime);
			++b;
		}
		else if ((*b)->isActive() == false)
		{
			b = m_enemyBulletList.erase(b);
		}
	}

	//Update mines
	for (auto m : m_playerShip->m_mineList)
	{
		m->update(elapsedTime);
	}

	//Updates all visual effects
	for (int i = 0; i < m_effectsList.size(); ++i)
	{
		if (m_effectsList[i]->m_destroyAnimation)
		{
			m_effectsList.erase(std::remove(m_effectsList.begin(), m_effectsList.end(), m_effectsList[i]));
		}
		else
		{
			m_effectsList[i]->update(elapsedTime);
		}
	}

	//Updates all explosions
	for (int i = 0; i < m_explosionList.size(); ++i)
	{
		if (m_explosionList[i]->m_destroyAnimation)
		{
			m_explosionList.erase(std::remove(m_explosionList.begin(), m_explosionList.end(), m_explosionList[i]));
		}
		else
		{
			m_explosionList[i]->update(elapsedTime);
		}
	}


	//Update Player Ship
	m_playerShip->update(elapsedTime);

	//Update Camera position
	m_camera.setPosition(m_playerShip->getWorldPosition());

	//update Next Wave Text position
	m_waveSprite->setPosition(m_playerShip->getPosition().x, m_playerShip->getPosition().y - 200);
	
	//Update HUD
	m_HUD.update(elapsedTime, m_playerShip->m_ability1Ready, m_playerShip->m_ability2Ready, m_playerShip->m_hull, m_score);
}

void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Render each game world layer with parallax factor >= 1.0
	for (auto c : m_gameWorldLayerList)
	{
		if (c->getParallaxFactor() >= 1.0f)
			target.draw(*c);
	}

	//Get camera view proj transform and set it to renderstate
	sf::RenderStates renderState;
	renderState.transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	//Render each game world layer with parallax factor <1.0
	for (auto c : m_gameWorldLayerList)
	{
		if (c->getParallaxFactor() < 1.0f)
			target.draw(*c);
	}

	//Draw all bullets
	for (auto c : m_bulletList)
	{
		target.draw(*c, renderState);
	}

	//Draw enemy bullets
	for (auto c : m_enemyBulletList)
	{
		target.draw(*c, renderState);
	}

	//Draw animations
	for (auto c : m_explosionList)
	{
		target.draw(*c, renderState);
		if (c)
			target.draw(c->m_scoreText, renderState);
	}

	//Draw the sprite object with the renderstate
	for (auto c : m_staticObjectList)
	{
		target.draw(*c, renderState);
	}
	
	//Draw all enemy ships
	for (auto c : m_enemyShipList)
	{
		target.draw(*c, renderState);
		target.draw(*c->m_navArrow, renderState);
	}

	//Draw Tractor Beam
	if (m_playerShip->m_tractorBeam)
		target.draw((*m_playerShip->m_tractorBeam), renderState);

	//Draw Shield
	if (m_playerShip->m_shieldActive)
		target.draw(*m_playerShip->m_shield, renderState);

	//Draw player ship animations
	for (auto c : m_playerShip->m_playerShipEffects)
	{
		target.draw(*c, renderState);
	}

	//Draw enemy ship animations
	for (auto c : m_enemyShip->m_enemyShipEffects)
	{
		target.draw(*c, renderState);
	}

	//Draw all remaining visual effects
	for (auto c : m_effectsList)
	{
		target.draw(*c, renderState);
	}

	//Draw Mine
	for (auto c : m_playerShip->m_mineList)
	{
		target.draw(*c, renderState);
	}

	//Draw HUD
	target.draw(m_HUD, renderState);
}

void GameWorld::spawnEnemies()
{
	//Spawns enemies in a circle around player ships current position
	if (m_enemyShipList.size() == 0)
	{
 		while (m_enemyShipList.size() < m_numberOfEnemies)
		{
			m_enemyShip = new EnemyShip();
			m_enemyShip->setDefaultTexture("Media/Textures/enemyship.png");

			m_enemyShip->setPosition(m_Maths->parametricCircle(static_cast <float> (rand() % 360), (m_windowWidth * 0.8f) + rand() % 100, m_playerShip->getPosition()));
			m_enemyShip->setTargetLocation(m_playerShip->getPosition());
			m_enemyShipList.push_back(m_enemyShip);
		}
	}
}

void GameWorld::createExplosion(sf::Vector2f enemyShipPosition)
{
	//Creates explosion animation at enemyships position
	m_explosion = new Explosion("Media/Textures/explosion.png", "Media/SpriteInfo/explosion.txt", 1.0f);
	m_explosion->setPosition(enemyShipPosition);
	m_explosionList.push_back(m_explosion);
	m_score += 1000;
}

void GameWorld::checkIfInMineRange(sf::Vector2f minePosition)
{
	//Function that checks is enemyships are within a predefined range
	//when mine explodes. If they are, they are destroyed.

	for (auto c = m_enemyShipList.begin(); c != m_enemyShipList.end();)
	{
		if ((*c)->checkCollision((*c)->getPosition(), minePosition, 400.0f))
		{
			
			createExplosion((*c)->getPosition());
			c = m_enemyShipList.erase(c);
			break;
		}
		else
		{
			++c;
		}
	}
}

void GameWorld::collisionChecks(sf::Time elapsedTime)
{
	//Function to check all collisions within the game and 
	//update the GameWorld accordingly.

	//Check collisions between enemyships and playership
	for (auto c = m_enemyShipList.begin(); c != m_enemyShipList.end();)
	{
		bool collision = false;

		if (m_playerShip->checkCollision(m_playerShip->getPosition(), (*c)->getPosition(), m_playerShip->getGlobalBounds().width * 0.7f))
		{
			createExplosion((*c)->getPosition());
			c = m_enemyShipList.erase(c);
			m_playerShip->m_hull -= 20;
			collision = true;
		}
		if (collision == false)
			++c;
	}

	//Check collisions between enemyships and mines
	for (auto m = m_playerShip->m_mineList.begin(); m != m_playerShip->m_mineList.end();)
	{
		bool hit = false;

		for (auto c = m_enemyShipList.begin(); c != m_enemyShipList.end();)
		{
			if ((*c)->checkCollision((*c)->getPosition(), (*m)->getPosition(), (*c)->getGlobalBounds().width * 0.7f))
			{
				sf::Vector2f position = (*m)->getPosition();
				m = m_playerShip->m_mineList.erase(m);

				//Create mine explosion
				m_mineExplosion = new EffectsAnimations("Media/Textures/mineExplosion.png", "Media/SpriteInfo/mineExplosion.txt", 1.0f);
				m_mineExplosion->setPosition((*c)->getPosition());
				m_effectsList.push_back(m_mineExplosion);

				checkIfInMineRange(position);

				hit = true;
				break;
			}
			else
			{
				++c;
			}
		}
		if (hit == false)
		{
			++m;
		}
	}

	//Checks collisions between enemyships and players bullets
	for (auto b = m_bulletList.begin(); b != m_bulletList.end();)
	{
		if ((*b)->isActive())
		{
			bool hit = false;

			for (auto c = m_enemyShipList.begin(); c != m_enemyShipList.end();)
			{
				if ((*c)->checkCollision((*c)->getPosition(), (*b)->getPosition(), (*c)->getGlobalBounds().width * 0.7f))
				{
					createExplosion((*c)->getPosition());
					b = m_bulletList.erase(b);
					c = m_enemyShipList.erase(c);
					++m_enemiesKilled;
					hit = true;
					break;
				}
				else
				{
					++c;
				}
			}
			if (hit == false)
				++b;
		}
		else if ((*b)->isActive() == false)
		{
			b = m_bulletList.erase(b);
		}
	}

	//Checks collisions between enemy bullets and playership
	for (auto b = m_enemyBulletList.begin(); b != m_enemyBulletList.end();)
	{
		if ((*b)->isActive())
		{
			bool hit = false;

			if (m_playerShip->checkCollision(m_playerShip->getPosition(), (*b)->getPosition(), m_playerShip->getGlobalBounds().width * 0.7f))
			{
				b = m_enemyBulletList.erase(b);
				if (m_playerShip->m_shieldActive == false)
				{
					m_playerShip->m_hull -= 20;
				}
				hit = true;
				break;
			}
			else
			{
				++b;
			}
		}
		else if ((*b)->isActive() == false)
		{
			b = m_enemyBulletList.erase(b);
		}
	}
}

void GameWorld::resetGame()
{
	//Resets game to original state
	m_enemyBulletList.clear();
	m_bulletList.clear();
	m_enemyShipList.clear();
	m_effectsList.clear();
	m_explosionList.clear();
	m_playerShip->m_mineList.clear();
	m_HUD.m_gameStarted = false;
	m_enemiesKilled = 0;
	m_playerShip->setPosition(0, 0);
	spawnEnemies();
}