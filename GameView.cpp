#include "GameView.h"

void GameView::setGameTileTexture(const std::string& textureFilename)
{
	m_txrGameTiles.loadFromFile(textureFilename);
	m_txrGameTiles.setSmooth(true);
	auto sizeTexture = m_txrGameTiles.getSize();
	int numTiles = sizeTexture.x / m_cPxGameTile;
	m_arrGameTiles.resize(numTiles);
	
	for (int i = 0; i < numTiles; i++)
		m_arrGameTiles[i] = sf::Sprite(m_txrGameTiles, sf::IntRect(m_cPxGameTile * i, 0, m_cPxGameTile, m_cPxGameTile));
}

void GameView::setSmileTileTexture(const std::string& textureFilename)
{
	m_txrSmileTiles.loadFromFile(textureFilename);
	m_txrSmileTiles.setSmooth(true);
	auto sizeTexture = m_txrSmileTiles.getSize();
	int numTiles = sizeTexture.x / m_cPxSmileTile;
	m_arrSmileTiles.resize(numTiles);

	for (int i = 0; i < numTiles; i++)
	{
		m_arrSmileTiles[i] = sf::Sprite(m_txrSmileTiles, sf::IntRect(m_cPxSmileTile * i, 0, m_cPxSmileTile, m_cPxSmileTile));
		m_arrSmileTiles[i].setScale(0.5, 0.5);
	}
}

void GameView::drawGameTile(const int nGameTile, const int xPos, const int yPos)
{
	m_arrGameTiles[nGameTile].setPosition(static_cast<float>((xPos * m_cPxGameTile) + m_cPxXBegin), static_cast<float>((yPos * m_cPxGameTile) + m_cPxYBegin));
	m_rwWindow.draw(m_arrGameTiles[nGameTile]);
}

void GameView::drawMenu(const int nSmileTile)
{
	auto sprLeftBorder = sf::Sprite(m_txrGameTiles, sf::IntRect(m_cPxGameTile * m_cNumUnopenedTile, 0, 5, m_cPxGameTile));
	auto sprRightBorder = sf::Sprite(m_txrGameTiles, sf::IntRect((m_cPxGameTile * (m_cNumUnopenedTile + 1) - 5), 0, 5, m_cPxGameTile));
	auto sprMiddle = sf::Sprite(m_txrGameTiles, sf::IntRect((m_cPxGameTile * m_cNumUnopenedTile) + 5, 0, 22, m_cPxGameTile));

	sprLeftBorder.setScale(1, 2.375);
	sprRightBorder.setScale(1, 2.375);
	sprMiddle.setScale(static_cast<float>(18.2), 2.375);

	sprLeftBorder.setPosition(0,0);
	sprRightBorder.setPosition(395, 0);
	sprMiddle.setPosition(5, 0);

	m_rwWindow.draw(sprMiddle);
	m_rwWindow.draw(sprLeftBorder);
	m_rwWindow.draw(sprRightBorder);

	m_arrSmileTiles[nSmileTile].setPosition(static_cast<float>(m_cPxSmileXPos), static_cast<float>(m_cPxSmileYPos));
	m_rwWindow.draw(m_arrSmileTiles[nSmileTile]);
}

const GameView::MouseLocation GameView::defineMouseLocation(const int* nFieldHeight, const int* nFieldsWidth)
{
	MouseLocation mouseLoc{ LocationGroup::OTHER, -1, -1 };

	const auto mousePos = sf::Mouse::getPosition(m_rwWindow);

	if (mousePos.x >= m_cPxSmileXPos and mousePos.x <= m_cPxSmileXPos + (m_cPxSmileTile * 0.5)
		and mousePos.y > m_cPxSmileYPos and mousePos.y < m_cPxSmileYPos + (m_cPxSmileTile * 0.5))
		mouseLoc.nGrp = LocationGroup::SMILE_TILE;

	else if (mousePos.x >= m_cPxXBegin and mousePos.x <= m_cPxXBegin + m_cPxGameTile * *nFieldsWidth
		and mousePos.y > m_cPxYBegin and mousePos.y < m_cPxYBegin + m_cPxGameTile * *nFieldHeight)
	{
		mouseLoc.nGrp = LocationGroup::GAME_TILE;
		mouseLoc.nFieldRow = (mousePos.y - m_cPxYBegin) / m_cPxGameTile;
		mouseLoc.nFieldColumn = (mousePos.x - m_cPxXBegin) / m_cPxGameTile;
	}

	return mouseLoc;
}
