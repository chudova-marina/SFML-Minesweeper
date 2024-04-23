#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <vector>

class GameView
{
public:
	GameView(sf::RenderWindow& window) : m_rwWindow(window) {};

	const enum LocationGroup
	{
		SMILE_TILE,
		GAME_TILE,
		OTHER,
		MAX_LOC_GROUPS
	};

	struct MouseLocation
	{
		LocationGroup nGrp;
		int nFieldRow, nFieldColumn;
	};

	void setGameTileTexture(const std::string& textureFilename);
	void setSmileTileTexture(const std::string& textureFilename);

	void drawGameTile(const int nGameTile, const int xPos, const int yPos);
	void drawMenu(const int nSmileTile);

	const MouseLocation defineMouseLocation(const int* nFieldHeight, const int* nFieldsWidth);

private:
	sf::RenderWindow& m_rwWindow;

	const int m_cPxGameTile = 32; // A game tile side in pixels
	const int m_cPxSmileTile = 77; // A smile tile side in pixels
	const int m_cPxXBegin = 40, m_cPxYBegin = 76; // Starting coordinates of the field 
	const int m_cNumUnopenedTile = 10; // Number of the "unopened" tile in the file
	const int m_cPxSmileXPos = 182, m_cPxSmileYPos = 20; // Starting coordinates of the Smile tile
	std::vector<sf::Sprite> m_arrGameTiles{};
	std::vector<sf::Sprite> m_arrSmileTiles{};
	sf::Texture m_txrGameTiles{};
	sf::Texture m_txrSmileTiles{};
	sf::Sprite m_sprButton;
};

