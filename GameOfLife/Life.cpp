#include "Life.h"
#include "stdafx.h"
#include "Game.h"

Life::Life() :
	_generations(0)
{
	/*Load("images/cell.png");
	assert(IsLoaded());

	GetSprite().SetCenter(cellWidth/2,cellWidth/2);
	*/

	assert(image.LoadFromFile("images/cell.png"));

	_sprite.SetImage(image);

	cellWidth = 10;
	//I don't think setcenter is needed
	//_sprite.SetCenter(cellWidth/2,cellWidth/2);
	GRID_WIDTH = Game::GAMEAREA_WIDTH/cellWidth;
	GRID_HEIGHT = Game::GAMEAREA_HEIGHT/cellWidth;

	//initialise vector array to false
	grid.assign(GRID_WIDTH, std::vector<bool> (GRID_HEIGHT, false));
/*
	//creates a stable block to test
	grid.at(50).at(50) = true;
	grid.at(51).at(50) = true;
	grid.at(50).at(51) = true;
	grid.at(51).at(51) = true;

	//creates a glider
	grid.at(20).at(50) = true;
	grid.at(21).at(50) = true;
	grid.at(22).at(50) = true;
	grid.at(22).at(51) = true;
	grid.at(21).at(52) = true;
	*/
/*
	//Draws Die hard
	grid.at(20).at(20) = true;
	grid.at(21).at(20) = true;
	grid.at(21).at(21) = true;

	grid.at(25).at(21) = true;
	grid.at(26).at(21) = true;
	grid.at(26).at(19) = true;
	grid.at(27).at(21) = true;
*/
	grid.at(0).at(0) = true;
	grid.at(0).at(1)= true;
	grid.at(0).at(2) = true;
	grid.at(0).at(3) = true;
}

void Life::Update()
{
	std::vector< std::vector<bool> > grid_temp = grid;

	for(std::vector< std::vector<bool> >::size_type i = 0; i != grid.size(); i++)
	{
		for(std::vector<bool>::size_type j = 0; j != grid[i].size() ; j++)
		{
			if(checkCell(i,j))
			{
				grid_temp[i][j] = true;
				Draw(i, j);
			}
			else grid_temp[i][j] = false;

		}

	}
	grid = grid_temp;
	_generations++;
}

void Life::Draw(int x, int y)
{
		_sprite.SetPosition(x*cellWidth,y*cellWidth );
		Game::GetWindow().Draw(_sprite);
}
void Life::DrawAll()
{//loop over every cell and draw each one

	for(std::vector< std::vector<bool> >::size_type i = 0; i != grid.size(); i++)
	{
		for(std::vector<bool>::size_type j = 0; j != grid[i].size() ; j++)
		{
			if(grid[i][j]) Draw(i, j);
		}

	}
}
//takes x y co-ords of the desired cell and inverts its state
void Life::ToggleCell(int x, int y)
{
	if(Life::grid.at(x).at(y))
	{
		grid.at(x).at(y) = false;
	}
	else
	{
		Life::grid.at(x).at(y) = true;
		//Draw(x, y);
	}
		
}

//returns true if cell should be alive and false if it should be dead
bool Life::checkCell(int x, int y)
{
	int neighbour = 0;
	int cellsX[8];
	int cellsY[8];
	// [0][1][2]
	// [3][X][4]
	// [5][6][7]
	//cell is on the left edge
	if(!x)
	{
		cellsX[0] = GRID_WIDTH-1;
		cellsX[3] = GRID_WIDTH-1;
		cellsX[5] = GRID_WIDTH-1;
	}
	else
	{
		cellsX[0] = x-1;
		cellsX[3] = x-1;
		cellsX[5] = x-1;
	}
	//cell is on the right edge
	if(x == (GRID_WIDTH-1))
	{
		cellsX[2] = 0;
		cellsX[4] = 0;
		cellsX[7] = 0;
	}
	else
	{
		cellsX[2] = x+1;
		cellsX[4] = x+1;
		cellsX[7] = x+1;
	}
	//cell is on the top edge
	if(!y)
	{
		cellsY[0] = GRID_HEIGHT-1;
		cellsY[1] = GRID_HEIGHT-1;
		cellsY[2] = GRID_HEIGHT-1;
	}
	else
	{
		cellsY[0] = y-1;
		cellsY[1] = y-1;
		cellsY[2] = y-1;
	}
	if(y == (GRID_HEIGHT-1))
	{
		cellsY[5] = 0;
		cellsY[6] = 0;
		cellsY[7] = 0;
	}
	else
	{
		cellsY[5] = y+1;
		cellsY[6] = y+1;
		cellsY[7] = y+1;
	}
	cellsX[1]=x; cellsX[6]=x; cellsY[3]=y; cellsY[4]=y;
	
	for(int i = 0; i < 8; i++)
	{
		if(grid[cellsX[i]][cellsY[i]])
		neighbour++;
	}
		
	//If a cell is alive and has less than 2 or more than 3 neighbours then it dies
	//If a cell is dead and has exactly 3 neighbours then it comes to life

	if(grid[x][y])
	{
		if((neighbour < 2) || (neighbour > 3))
			return false;
		return true;
	}
	if(neighbour == 3) return true;

	return false;
}

int Life::GetCellWidth()
{
	return cellWidth;
}

void Life::OutputGrid()
{
	//create file to store data
	//overwrites any existing file with the same name, intended behaviour
	//Output file is rotated 90 degrees due the way the grid is stored
	//The x position being the outer vector
	std::ofstream file;
	file.open("grid.txt", std::ios::out | std::ios::trunc );
	
	for(std::vector< std::vector<bool> >::size_type i = 0; i != grid.size(); i++)
	{
		for(std::vector<bool>::size_type j = 0; j != grid[i].size() ; j++)
		{
			//if a cell is alive, write a 1 to the file in that position else write a 0
			grid[i][j] ? file << "1" : file << "0";
		}
		file << std::endl;
	}
	file.close();
}

void Life::InputGrid()
{
	char chr;
	std::ifstream file;
	int i = 0;
	int j = 0;

	file.open("grid.txt");
	if(file.is_open())
	{
		while(file.good())
		{
			file.get(chr);
			if (chr == '\n')
			{ 
				++i;
				j = 0;
				continue;
			}
			if(chr == '0') grid[i][j] = false; 
			else 
			{
					grid[i][j] = true;
					Draw(i,j);
			}
			j++;
		}
		file.close();
		//DrawAll();
	}

}