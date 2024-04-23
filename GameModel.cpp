#include "GameModel.h"

GameModel::GameModel()
{
	for (int i = 0; i < m_cFieldWidth; i++)
		for (int j = 0; j < m_cFieldHeight; j++)
			m_arrFieldVisible[i][j] = GameTileType::EMPTY;

	m_nCurrSmileTile = SmileTileType::COOL;
	m_nCurrGameMode = GameMode::STANDBY;
	m_nNumOpenTiles = 0;
}

void GameModel::newGame()
{
	// Clean the field: close tiles, empty true tiles
	for (int i = 0; i < m_cFieldWidth; i++)
		for (int j = 0; j < m_cFieldHeight; j++)
		{
			m_arrFieldVisible[i][j] = GameTileType::UNOPENED;
			m_arrFieldTrue[i][j] = GameTileType::EMPTY;
		}

	// Set mines and numbers
	int minesNumber = 0;

	do
	{
		int nMineRow = static_cast<int>(m_mersenne() % m_cFieldHeight);
		int nMineColumn = static_cast<int>(m_mersenne() % m_cFieldWidth);

		if (m_arrFieldTrue[nMineColumn][nMineRow] != GameTileType::MINE)
		{
			m_arrFieldTrue[nMineColumn][nMineRow] = GameTileType::MINE;
			minesNumber++;
			setNumbersAroundMine(nMineRow, nMineColumn);
		}
	} while (minesNumber < m_cMinesNumber);

	// set default values to attributes
	m_nCurrSmileTile = SmileTileType::SMILE;
	m_nCurrGameMode = GameMode::PLAY;
	m_nNumOpenTiles = 0;
}

void GameModel::setNumbersAroundMine(const int nMineRow, const int nMineColumn)
{
	if (nMineColumn > 0)
	{
		setNumberTile(m_arrFieldTrue[nMineColumn - 1][nMineRow]);

		if (nMineRow > 0)
			setNumberTile(m_arrFieldTrue[nMineColumn - 1][nMineRow - 1]);

		if (nMineRow < (m_cFieldHeight - 1))
			setNumberTile(m_arrFieldTrue[nMineColumn - 1][nMineRow + 1]);
	}

	if (nMineColumn < (m_cFieldWidth - 1))
	{
		setNumberTile(m_arrFieldTrue[nMineColumn + 1][nMineRow]);

		if (nMineRow > 0)
			setNumberTile(m_arrFieldTrue[nMineColumn + 1][nMineRow - 1]);

		if (nMineRow < (m_cFieldHeight - 1))
			setNumberTile(m_arrFieldTrue[nMineColumn + 1][nMineRow + 1]);
	}

	if (nMineRow > 0)
		setNumberTile(m_arrFieldTrue[nMineColumn][nMineRow - 1]);

	if (nMineRow < (m_cFieldHeight - 1))
		setNumberTile(m_arrFieldTrue[nMineColumn][nMineRow + 1]);
}

void GameModel::setNumberTile(GameTileType &gameTile)
{
	switch (gameTile)
	{
	case GameTileType::EMPTY:
	case GameTileType::ONE:
	case GameTileType::TWO:
	case GameTileType::THREE:
	case GameTileType::FOUR:
	case GameTileType::FIVE:
	case GameTileType::SIX:
	case GameTileType::SEVEN:
		gameTile = static_cast<GameTileType>(static_cast<GameTileType>(1) + gameTile);
		break;
	default:
		break;
	}
}

void GameModel::processFlagTile(const int nRow, const int nColumn)
{
	switch (m_arrFieldVisible[nColumn][nRow])
	{
	case GameTileType::FLAG:
		m_arrFieldVisible[nColumn][nRow] = GameTileType::UNOPENED;
		break;
	case GameTileType::UNOPENED:
		m_arrFieldVisible[nColumn][nRow] = GameTileType::FLAG;
		break;
	default:
		break;
	}
}

void GameModel::getTrueGameTile(const int nRow, const int nColumn)
{
	if (m_arrFieldVisible[nColumn][nRow] != GameTileType::UNOPENED)
		return;

	switch (m_arrFieldTrue[nColumn][nRow])
	{
	case GameTileType::MINE: // if mine tile - instant lose
	{
		for (int i = 0; i < m_cFieldWidth; i++)
			for (int j = 0; j < m_cFieldHeight; j++)
				m_arrFieldVisible[i][j] = m_arrFieldTrue[i][j];

		m_nCurrSmileTile = SmileTileType::DEAD;
		m_nCurrGameMode = GameMode::LOSE;
		break;
	}
	case GameTileType::ONE:
	case GameTileType::TWO:
	case GameTileType::THREE:
	case GameTileType::FOUR:
	case GameTileType::FIVE:
	case GameTileType::SIX:
	case GameTileType::SEVEN:
	case GameTileType::EIGHT: // if number tile - just open this tile
	{
		m_arrFieldVisible[nColumn][nRow] = m_arrFieldTrue[nColumn][nRow];
		m_nNumOpenTiles++;
		m_nCurrSmileTile = SmileTileType::SMILE;
		break;
	}
	case GameTileType::EMPTY: // if empty tile - open all adjacent empty and number tiles
	{
		openAdjacentEmptyTiles(nRow, nColumn);

		m_nCurrSmileTile = SmileTileType::SMILE;
		break;
	}
	default:
		break;
	}

}

void GameModel::checkIfWin()
{
	if (m_nNumOpenTiles == (m_cFieldHeight * m_cFieldWidth) - m_cMinesNumber )
	{
		m_nCurrGameMode = GameMode::WIN;
		m_nCurrSmileTile = SmileTileType::COOL;
	}
}

void GameModel::openAdjacentEmptyTiles(const int nRow, const int nColumn)
{
	if (m_arrFieldVisible[nColumn][nRow] == m_arrFieldTrue[nColumn][nRow])
		return;

	m_arrFieldVisible[nColumn][nRow] = m_arrFieldTrue[nColumn][nRow];
	m_nNumOpenTiles++;

	if (m_arrFieldTrue[nColumn][nRow] != GameTileType::EMPTY)
		return;

	if (nColumn > 0)
	{
		openAdjacentEmptyTiles(nRow, nColumn - 1);

		if (nRow > 0)
			openAdjacentEmptyTiles(nRow - 1, nColumn - 1);

		if (nRow < (m_cFieldHeight - 1))
			openAdjacentEmptyTiles(nRow + 1, nColumn - 1);
	}

	if (nColumn < (m_cFieldWidth - 1))
	{
		openAdjacentEmptyTiles(nRow, nColumn + 1);

		if (nRow > 0)
			openAdjacentEmptyTiles(nRow - 1, nColumn + 1);

		if (nRow < (m_cFieldHeight - 1))
			openAdjacentEmptyTiles(nRow + 1, nColumn + 1);
	}

	if (nRow > 0)
		openAdjacentEmptyTiles(nRow - 1, nColumn);

	if (nRow < (m_cFieldHeight - 1))
		openAdjacentEmptyTiles(nRow + 1, nColumn);
}

const GameModel::field_t* GameModel::getFieldWithTiles()
{
	return &m_arrFieldVisible;
}

const GameModel::SmileTileType* const GameModel::getCurrSmileTile()
{
	return &m_nCurrSmileTile;
}

const GameModel::GameMode* const GameModel::getCurrGameMode()
{
	return &m_nCurrGameMode;
}

const int* const GameModel::getFieldHeight()
{
	return &m_cFieldHeight;
}

const int* const GameModel::getFieldWidth()
{
	return &m_cFieldWidth;
}

void GameModel::setCurrSmileTile(const SmileTileType& newSmileTile)
{
	m_nCurrSmileTile = newSmileTile;
}
