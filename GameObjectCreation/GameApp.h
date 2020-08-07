#pragma once

#include "raymath.h"
#include <vector>

class GameApp
{
public:

	GameApp();
	~GameApp();

	void Startup();

	void Run();

	void Update();
	void Draw();


private:

	int m_screenWidth;
	int m_screenHeight;

	int m_tileWidth;
	int m_tileHeight;

	Vector2 m_pacPos;
	Vector2 m_pacDir;

	float m_pacSpeed;

};


// Programming ideas
/*

	- bullet hell
	- tank game
	- liquid simulation
	- tetris
	- pong (in scope)
	- pacman (in scope)
	- - map
	- - - empty     0
	- - - walls		1
	- - - food		2
	- - - powerup	3

	[

		[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
		[1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
		[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],

	]


	- - player
	- - 
	- space invaders (maybe in scope)
	- render a 3d cube (); maybe in scope wiht build in raylib
	- fps (not in scope)
	- wackamol (maybe in scope)
	- snake (in scope)
	- frogger (maybe in scope)
	- duck hunt (in scope)
	- bad particle system (maybe in scope)
	- breakout (in scope)

*/




