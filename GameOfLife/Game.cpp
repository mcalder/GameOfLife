#include "stdafx.h"
#include "Game.h"
#include <button.hpp>

void Game::Start(void)
{
	if(_gamestate != Uninitialised)
		return;

	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "The Game of Life");

	//life = new Life();

	_gamestate = Paused;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.Close();
}

bool Game::IsExiting()
{
	if(_gamestate == Exiting)
		return true;
	else return false;
}


void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);

	switch(_gamestate)
	{
	case Paused:
		{
			if(currentEvent.Type == sf::Event::Closed) _gamestate = Exiting;

			if(currentEvent.Type == sf::Event::KeyPressed)
			{
				if(currentEvent.Key.Code == sf::Key::O) life->OutputGrid();
				else if(currentEvent.Key.Code == sf::Key::I) 
				{
					life->InputGrid();
					_mainWindow.Display();
				}
				else {_gamestate = Playing;}
			}
			if(currentEvent.Type == sf::Event::MouseButtonPressed)
			{
				HandleClick(currentEvent.MouseButton.X, currentEvent.MouseButton.Y);
			}			
		

		break;
		}
	case Playing:
		{
			if(Clock.GetElapsedTime() > updateRate)
			{//Update state every updateRate
				_mainWindow.Clear(sf::Color(0,0,0));
			
				life->Update();

				_mainWindow.Display();
				Clock.Reset();
			}
			
			if(currentEvent.Type == sf::Event::Closed) _gamestate = Exiting;
			if(currentEvent.Type == sf::Event::KeyPressed)
			{
				_gamestate = Paused;
			}
			
			break;
				
		}
	}
	
}
void Game::HandleClick(int x, int y)
{
	//checks mouseclick is within game bounds
	if((x >= 0 && x < GAMEAREA_WIDTH) && (y >= 0 && y < GAMEAREA_HEIGHT))
	{//toggle the clicked cell by converting the screen co-ord to the equivalent grid co-ord
		_mainWindow.Clear(sf::Color(0,0,0));
		life->ToggleCell(x/(life->GetCellWidth()),y/(life->GetCellWidth()));
		life->DrawAll();
		//DrawMenu();
		_mainWindow.Display();

	}
	else if(x > GAMEAREA_WIDTH && x <SCREEN_WIDTH)
	{//within the menu area
		
	}

}
sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

void Game::DrawMenu()
{//draws the menu options outside of the game area

}
	
	
Game::GameState Game::_gamestate = Uninitialised;
sf::RenderWindow Game::_mainWindow;
Life *Game::life = new Life();
sf::Clock Game::Clock;
float Game::updateRate = 0.5;
