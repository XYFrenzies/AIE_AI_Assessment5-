#include "EndGameState.h"
#include "raylib.h"


EndGameState::EndGameState() : m_screenWidth(), m_screenHeight()
{
}

EndGameState::~EndGameState()
{
}

void EndGameState::Startup()
{
	m_screenWidth = 1080;//Setting value of width of screen
	m_screenHeight = 720;//Setting value of height of screen
	InitWindow(m_screenWidth, m_screenHeight, "Game Over");
	SetTargetFPS(60);
}

void EndGameState::Run()
{
	Load();//Loads information first
	while (!WindowShouldClose())//While the program has not closed
	{
		//float dt = GetFrameTime();//Grab the delta time value
		//if (dt > 1.0f / 12.0f) dt = 1.0f / 12.0f;

		//Update(dt);//UYpdate per delta Time
		Draw();
	}
	Unload();//Deletes any bits in memory not unloaded yet
}

void EndGameState::Draw()
{
	DrawText(FormatText("Score: %i", ), 10, 10, 24, RAYWHITE);//Creates the text for the score.
}

