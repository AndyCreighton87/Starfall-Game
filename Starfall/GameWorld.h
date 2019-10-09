#ifndef GAMEWORLD
#define GAMEWORLD

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>
#include "GameWorldLayer.h"
#include "Camera.h"
#include "SpriteObject.h"
#include "AnimatedSpriteObject.h"
#include "SpriteAnimation.h"
#include "EnemyShip.h"
#include "PlayerShip.h"
#include "Bullet.h"
#include "Explosion.h"
#include "EffectsAnimations.h"
#include "HUD.h"

class GameWorld :
	public sf::Drawable, public sf::Transformable
{
public:
	GameWorld(int& windowWidth, int& windowHeight, sf::RenderWindow* parentWindow);
	~GameWorld();

	void				update(sf::Time& elapsedTime);
	void				resetGame();

	PlayerShip*			m_playerShip;
	HUD					m_HUD;

	int					m_score;
	
private:
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void				processEvents(sf::Time& elapsedTime);
	void				spawnEnemies();
	void				createExplosion(sf::Vector2f enemyShipPosition);
	void				checkIfInMineRange(sf::Vector2f minePosition);
	void				collisionChecks(sf::Time elapsedTime);

	static bool			layerSort(GameWorldLayer* a, GameWorldLayer* b);
	
	bool				m_waveIsShown;
	bool				m_ability1Ready;
	bool				m_ability2Ready;

	int					m_windowWidth;
	int					m_windowHeight;
	int					m_numberOfEnemies;
	int					m_enemiesKilled;

	Camera				m_camera;

	sf::Vector2f		m_cameraPosition;
	sf::RenderWindow*	m_parentWindow;

	EnemyShip*			m_enemyShip;
	Explosion*			m_explosion;
	EffectsAnimations*	m_mineExplosion;
	EffectsAnimations*	m_effects;

	SpriteObject*		m_background;
	SpriteObject*		m_waveSprite;
	SpriteAnimation*	m_currentAnimation;

	Maths*				m_Maths;

	std::vector<EnemyShip*>			m_enemyShipList;
	std::vector<SpriteObject*>		m_staticObjectList;
	std::vector<Bullet*>			m_bulletList;
	std::vector<Bullet*>			m_enemyBulletList;
	std::vector<GameWorldLayer*>	m_gameWorldLayerList;
	std::vector<Explosion*>			m_explosionList;
	std::vector<EffectsAnimations*> m_effectsList;

	sf::Font			m_gameFont;
	sf::Color			m_textColour;
	sf::Color			m_outlineColour;
	sf::Color			m_textHide;
	sf::Color			m_outlineHide;

	sf::Time			m_waveElapsed;
	sf::Time			m_waveTimer;
	sf::Time			m_ability1Elapsed;
	sf::Time			m_ability2Elapsed;
	sf::Time			m_abilityCooldown;
};
#endif