#include <SFML/Graphics.hpp>
#include "GameControl.h"
#include <memory>

int main()
{
	const int windowWidthPx{ 400 }, windowHeightPx{ 400 };
	sf::RenderWindow app(sf::VideoMode(windowWidthPx, windowHeightPx), "Minesweeper!");
	GameControl oGame(app);
	auto clrGrey = sf::Color(20, 20, 20, 255);

	oGame.setTextureGameTiles("Files\\tiles.jpg");
	oGame.setTextureSmileTiles("Files\\smileTiles.jpg");

	while (app.isOpen())
	{
		sf::Event event;

		while (app.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				app.close();
			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					oGame.onMouseLeftHold();
					break;
				case sf::Mouse::Right:
					oGame.onMouseRight();
					break;
				default:
					break;
				}
			case sf::Event::MouseButtonReleased:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						oGame.onMouseLeftHold();
					else
						oGame.onMouseLeftReleased();
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		app.clear(clrGrey);
		oGame.drawMenu();
		oGame.drawField();
		app.display();
	}
	return 0;
}
