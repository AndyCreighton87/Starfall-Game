#include "Maths.h"

Maths::Maths()
{
}

Maths::~Maths()
{
}

sf::Vector2f Maths::parametricCircle(float angle, float radius, sf::Vector2f position)
{
	float xPos = position.x + radius * cos(angle);
	float yPos = position.y + radius * sin(angle);

	sf::Vector2f point(xPos, yPos);

	return point;
}

float Maths::dotProduct(sf::Vector2f firstPosition, sf::Vector2f secondPosition)
{
	float dot = (firstPosition.x * secondPosition.x + firstPosition.y * secondPosition.y);

	return dot;
}

float Maths::L2Norm(sf::Vector2f position)
{
	float distance = sqrt(position.x * position.x + position.y * position.y);

	return distance;
}

sf::Vector2f Maths::Normalise(sf::Vector2f position)
{
	sf::Vector2f norm = position;

	float L2 = L2Norm(position);

	if (L2 != 0)
	{
		norm = sf::Vector2f((norm.x / L2), (norm.y / L2));
		return norm;
	}
	else
	{
		return sf::Vector2f(0, 0);
	}
}
