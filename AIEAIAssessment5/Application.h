#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "Player.h"
#include "Graph2D.h"
#include "Police.h"
#include "MoneyBags.h"
#include <map>
class Graph2D;
class Graph2DEditor;
class TileMap;


enum MAP
{
	WALL = 0,
	Obstacles = 1,
	MoneyBag = 2,
	Robber = 3,
	Policeman = 4,
	Ground = 5
};

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

	Vector2 GetMousePosWorld();
	Graph2D* GetGraph();
	Player* GetPlayer();

	void SmoothCameraFollow(Vector2 targetPos, float dt);

protected:
	int m_screenWidth;
	int m_screenHeight;





	TileMap* m_tile = nullptr;
	Camera2D m_camera = { 0 };
	Rectangle view = { 0, 0, 1440, 900 };


	Player* m_robber1 = nullptr;
	Police* m_police1 = nullptr;
	MoneyBags* m_money = new MoneyBags();

	Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;
	Graph2D::Node* m_startNode;
	Graph2D::Node* m_endNode;
private:
};

