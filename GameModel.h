#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <array>
#include <queue>

class GameModel
{
public:
	GameModel();

	const enum GameTileType
	{
		EMPTY,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		MINE,
		UNOPENED,
		FLAG,
		MAX_GAME_TILES,
	};

	const enum SmileTileType
	{
		SMILE,
		OH,
		COOL,
		DEAD,
		MAX_SMILE_TILES
	};

	const enum GameMode
	{
		STANDBY,
		PLAY,
		WIN,
		LOSE,
		MAX_GAME_MODES
	};

private:
	static const int m_cFieldHeight = 10;
	static const int m_cFieldWidth = 10;

	static const int m_cMinesNumber = 10;

	std::random_device m_rd;
	std::mt19937 m_mersenne{ m_rd() };

	using field_t = std::array<std::array<GameTileType, m_cFieldWidth>, m_cFieldHeight>;
	field_t m_arrFieldVisible{};
	field_t m_arrFieldTrue{};

	SmileTileType m_nCurrSmileTile;
	GameMode m_nCurrGameMode;
	int m_nNumOpenTiles;

	void setNumbersAroundMine(const int nMineRow, const int nMineColumn);
	void setNumberTile(GameTileType &gameTile);
	void openAdjacentEmptyTiles(const int nRow, const int nColumn);

public:
	const field_t* getFieldWithTiles();
	const SmileTileType* const getCurrSmileTile();
	const GameMode* const getCurrGameMode();
	const int* const getFieldHeight();
	const int* const getFieldWidth();
	void setCurrSmileTile(const SmileTileType& newSmileTile);

	void newGame();

	void processFlagTile(const int nRow, const int nColumn);
	void getTrueGameTile(const int nRow, const int nColumn);
	void checkIfWin();
};

