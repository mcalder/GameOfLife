#pragma once
#include "VisibleGameObject.h"
#include "Game.h"

class Life //:public VisibleGameObject
{
public:
	Life();

	void Update();
	void ToggleCell(int x, int y);
	void LiveCell(int x, int y);
	void DeadCell(int x, int y);
	void Draw(int x, int y);
	void DrawAll();
	int GetCellWidth();
	void OutputGrid();
	void InputGrid();

private:
	int _generations;
	bool checkCell(int x, int y);

	int cellWidth;

	int GRID_WIDTH;
	int GRID_HEIGHT;
	std::vector< std::vector<bool> > grid;

	sf::Image image;
	sf::Sprite _sprite;
};
