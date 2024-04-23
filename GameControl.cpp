#include "GameControl.h"

void GameControl::setTextureGameTiles(const std::string& textureFilename)
{
	m_oView.get()->setGameTileTexture(textureFilename);
}

void GameControl::setTextureSmileTiles(const std::string& textureFilename)
{
	m_oView.get()->setSmileTileTexture(textureFilename);
}

void GameControl::drawField()
{
	auto arrField = m_oModel.get()->getFieldWithTiles();

	for (int i = 0; i < arrField->size(); i++)
		for (int j = 0; j < arrField->at(i).size(); j++)
			m_oView.get()->drawGameTile(arrField->at(i).at(j), i, j);
}

void GameControl::drawMenu()
{
	m_oView.get()->drawMenu(int(*m_oModel.get()->getCurrSmileTile()));
}

void GameControl::onMouseLeftHold()
{
	if (*m_oModel.get()->getCurrGameMode() == m_oModel.get()->GameMode::PLAY)
		m_oModel.get()->setCurrSmileTile(m_oModel.get()->SmileTileType::OH);
}

void GameControl::onMouseLeftReleased()
{
	auto mouseLoc = m_oView.get()->defineMouseLocation(m_oModel.get()->getFieldHeight(), m_oModel.get()->getFieldWidth());
	auto gameMode = m_oModel.get()->getCurrGameMode();

	m_oModel.get()->setCurrSmileTile(m_oModel.get()->SmileTileType::SMILE);

	if (mouseLoc.nGrp == m_oView.get()->LocationGroup::SMILE_TILE)
		m_oModel.get()->newGame();
	else if (*gameMode == m_oModel.get()->GameMode::PLAY)
		if (mouseLoc.nGrp == m_oView.get()->LocationGroup::GAME_TILE)
		{
			m_oModel.get()->getTrueGameTile(mouseLoc.nFieldRow, mouseLoc.nFieldColumn);
			m_oModel.get()->checkIfWin();
		}
}

void GameControl::onMouseRight()
{
	auto mouseLoc = m_oView.get()->defineMouseLocation(m_oModel.get()->getFieldHeight(), m_oModel.get()->getFieldWidth());
	auto gameMode = m_oModel.get()->getCurrGameMode();

	if (*gameMode == m_oModel.get()->GameMode::PLAY
		and mouseLoc.nGrp == m_oView.get()->LocationGroup::GAME_TILE)
		m_oModel.get()->processFlagTile(mouseLoc.nFieldRow, mouseLoc.nFieldColumn);
}
