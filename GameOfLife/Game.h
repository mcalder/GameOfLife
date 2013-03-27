#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Life.h"

class Game
{
public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	static sf::Clock Clock;


	const static int SCREEN_WIDTH = 1000;
	const static int SCREEN_HEIGHT = 800;
	const static int GAMEAREA_WIDTH = SCREEN_WIDTH-200;
	const static int GAMEAREA_HEIGHT = SCREEN_HEIGHT;
	static void SetUpdateRate(float n);
	static float GetUpdateRate();


private:
	static bool IsExiting();
	static void GameLoop();
	static void HandleClick(int x, int y);
	static void DrawMenu();

	enum GameState{Uninitialised, Paused, Playing, Exiting};
	
	static Life *life;
	static GameState _gamestate;
	static sf::RenderWindow _mainWindow;
	static float updateRate;	//time between updates

};