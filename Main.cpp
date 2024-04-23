#include <SFML/Graphics.hpp>
#include "GameControl.h"
//#include <time.h>
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
/*
using namespace sf;

int main()
{
	RenderWindow app(VideoMode(500, 500), "Sandbox!");

	Texture t1;
	t1.loadFromFile("Files\\tiles.jpg");
	
	Sprite s(t1);

	bool isMove{ false };
	float dx{ 0 }, dy{ 0 };

	while (app.isOpen())
	{
		Event e;

		Vector2i pos{ Mouse::getPosition(app) };

		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					if (s.getGlobalBounds().contains(pos.x, pos.y))
					{
						isMove = true;
						dx = pos.x - s.getPosition().x;
						dy = pos.y - s.getPosition().y;
					}

			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Left)
					isMove = false;
		}

		if (isMove)
			s.setPosition(pos.x - dx, pos.y - dy);

		// draw
		app.clear();
		app.draw(s);
		app.display();
	}

	return 0;
}*/