#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "Player.h"
#include "Graph2D.h"
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

	void TestGraph();

protected:
	int m_screenWidth;
	int m_screenHeight;



	//Player* m_player1 = new Player();
	Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;
	Graph2D::Node* m_startNode;
	Graph2D::Node* m_endNode;
private:
};

