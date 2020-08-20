#pragma once
#include "Application.h"
class EndGameState
{
public:
	//Constructor
	EndGameState();
	//Deconstructor
	virtual ~EndGameState();

	void Startup();
	void Run();
	void Draw();

	void Load();
	void Unload();
protected:
	//Gets screenwidth and height of the screen
	int m_screenWidth;
	int m_screenHeight;

	Application* app;
private:

};

