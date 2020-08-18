#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "Player.h"
#include "Graph2D.h"
#include "Police.h"
#include "MoneyBags.h"
class Graph2D;
class Graph2DEditor;
class TileMap;

class Application
{
public:
	//Constructor
	Application();
	//Deconstructor
	virtual ~Application();

	void Startup();
	void Run();
	void Update(float dt);
	void Draw();
	
	void Load();
	void Unload();

	Vector2 GetMousePosWorld();//Gets the position of the mouse within the world
	Graph2D* GetGraph();//Gets the graph information from a point in memory
	Player* GetPlayer();//Gets the players information from a point in memory
	Item* GetItem();//Gets the moneys information from a point in memory
	Police* GetPolice();//Gets the enemy's information from a point in memory
	void SmoothCameraFollow(Vector2 targetPos, float dt);//This is the physics behind the smooth flow of the camera.
protected:
	//Gets screenwidth and height of the screen
	int m_screenWidth;
	int m_screenHeight;
	int count = 0;//This is for the score which is initialized at 0

	TileMap* m_tile = nullptr;//Tiles from tiled is set to nullptr
	Camera2D m_camera = { 0 };//The camera is set to 0
	Rectangle view = { 0, 0, 1440, 900 };//Creates a default rectangle


	Player* m_robber = nullptr;//This is the instance of the player called robber
	Police* m_police = nullptr;//This is the instance of the enemy called police
	Item* m_item = nullptr;//Money is the variable that spawns in random locations, its set to nullptr

	Graph2D* m_graph = nullptr;//This is the graph that uses functions within the 2D graph
	Graph2DEditor* m_graphEditor = nullptr;//This is the editing graph.
private:
};

