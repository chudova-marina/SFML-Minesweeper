#pragma once
#include <memory>
#include "GameModel.h"
#include "GameView.h"

class GameControl
{
public:
	GameControl(sf::RenderWindow& window)
	{
		m_oView = std::make_unique<GameView>(window);
		m_oModel = std::make_unique<GameModel>();
	};

	void setTextureGameTiles(const std::string& textureFilename);
	void setTextureSmileTiles(const std::string& textureFilename);
	void drawField();
	void drawMenu();
	void onMouseLeftHold();
	void onMouseLeftReleased();
	void onMouseRight();

private:
	std::unique_ptr<GameView> m_oView;
	std::unique_ptr<GameModel> m_oModel;
};

