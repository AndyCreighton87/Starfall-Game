#ifndef MATHS
#define MATHS

#include <SFML/Graphics.hpp>


static const float		PI = 3.1415f;

class Maths
{
public:
	Maths();
	~Maths();

	sf::Vector2f		parametricCircle(float angle, float radius, sf::Vector2f position);
	float				dotProduct(sf::Vector2f firstPosition, sf::Vector2f secondPosition);
	float				L2Norm(sf::Vector2f position);
	sf::Vector2f		Normalise(sf::Vector2f position);
};

#endif