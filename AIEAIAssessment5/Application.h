#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "Player.h"
#include "Graph2D.h"
#include "Police.h"
#include "MoneyBags.h"
class Graph2D;
class Graph2DEditor;

class Application
{
public:

	enum gameMap
	{
		ground = 0,
		boarder = 1,
		moneyBag = 2,
		robber = 3,
		police = 4

	};

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



	Player* m_robber1 = new Player();
	Police* m_police1 = new Police();
	MoneyBags* m_money = new MoneyBags();

	Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;
	Graph2D::Node* m_startNode;
	Graph2D::Node* m_endNode;
private:

	static const int MAP_ROWS = 20;
	static const int MAP_COLS = 15;

	int m_map[MAP_ROWS][MAP_COLS] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ,
		{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
		{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};


};

