#include <SFML/graphics.hpp>
#include "Application.h"

int main()
{
#ifdef _DEBUG
	Application app(1280, 720, sf::Style::Default);
#else
	Application app(1920, 1080, sf::Style::Fullscreen);
#endif

	app.run();

	return 0;
}
