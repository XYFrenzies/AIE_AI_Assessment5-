#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "Player.h"

class Graph2D;
class Graph2DEditor;

class Application
{
public:
	Application();
	virtual ~Application();

	void Startup();
	void Run();
	void Update(float dt);
	void Draw();
	
	void Load();
	void Unload();


protected:
	int m_screenWidth;
	int m_screenHeight;
	Player* m_player1 = new Player();
	Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;

private:
};

