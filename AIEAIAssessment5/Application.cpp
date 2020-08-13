#include "Application.h"

#include "Behaviour.h"
#include "KeyBoardBehaviour.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"
#include "TileMap.h"
#include "TileMapRenderer.h"

Application::Application() : m_screenWidth(), m_screenHeight()
{
}

Application::~Application()
{
}
//The beginning of the project
void Application::Startup()
{
	m_screenWidth = 1080;//Setting value of width of screen
	m_screenHeight = 720;//Setting value of height of screen
	InitWindow(m_screenWidth, m_screenHeight, "Hello World");
	SetTargetFPS(60);
}

void Application::Run()
{
	Load();//Loads information first
	while (!WindowShouldClose())//While the program has not closed
	{
		float dt = GetFrameTime();//Grab the delta time value
		if (dt > 1.0f / 12.0f) dt = 1.0f / 12.0f;

		Update(dt);//UYpdate per delta Time
		Draw();
	}
	Unload();//Deletes any bits in memory not unloaded yet
}

void Application::Update(float dt)
{



	auto barrier = m_tile->GetTileLayer("Barrier");//The barrier of the map
	auto obstacles = m_tile->GetTileLayer("Obstacles");//The trees and terrain of the map


	if (IsKeyDown(KEY_UP) && m_camera.zoom >= 0.5) m_camera.zoom -= 1 * dt;
	if (IsKeyDown(KEY_DOWN) && m_camera.zoom <= 10) m_camera.zoom += 1 * dt;

	if (IsKeyDown(KEY_TAB))
	{
		m_graphEditor->Update(dt);
	}
	
	m_robber1->Update(dt);//Updates player1 per deltatime
	m_police1->Update(dt);

	int playerXIndex = m_robber1->GetPosition().x / m_tile->tileWidth;
	int playerYIndex = m_robber1->GetPosition().y / m_tile->tileHeight;
	auto cptbar = barrier->GetTileData(playerXIndex, playerYIndex);
	auto cptobst = obstacles->GetTileData(playerXIndex, playerYIndex);
	m_robber1->SetFriction(0);
	if (cptobst.globalTileId != 0)
	{
		//newVel.x = 0.5f - m_robber1->GetPosition().x;//Sets the direction that the player is facing, towards the center via the x
		//newVel.y = 0.5f - m_robber1->GetPosition().y;//Sets the direction that the player is facing, towards the center via the y

		m_robber1->SetFriction(1);
		//newVel = Vector2Normalize(newVel);//
		//newVel = Vector2Scale(newVel, 50);
		// the player is on a barrior tile
	}

	if (cptbar.globalTileId != 0)
	{
		Vector2 newVel;
		newVel.x = GetScreenWidth() * 0.5f - m_robber1->GetPosition().x;//Sets the direction that the player is facing, towards the center via the x
		newVel.y = GetScreenHeight() * 0.5f - m_robber1->GetPosition().y;//Sets the direction that the player is facing, towards the center via the y

		newVel = Vector2Normalize(newVel);//
		newVel = Vector2Scale(newVel, m_robber1->GetMaxSpeed());
		m_robber1->SetVelocity(newVel);
	}



	//if (m_robber1->GetPosition().x == m_money->GetPosition().x && m_robber1->GetPosition().y == m_money->GetPosition().y)
	//{
	//	//moneyStorage.pop_back();
	//}


	SmoothCameraFollow(m_robber1->GetPosition(), dt);

}

void Application::Draw()
{
	BeginDrawing();

	ClearBackground(BLUE);//Black background


	BeginMode2D(m_camera);

	//Setting view port enables renderer
	//to only draw tiles that are visible.
	m_tile->GetRenderer()->SetView(view.x, view.y, view.width, view.height);

	// loop through each layer - invoke draw method
	for (int i = 0; i < m_tile->layers.size(); i++)
	{
		m_tile->DrawLayer(m_tile->layers[i]);
		// draw player on layer 1 (underneith walls / trees)
		if (i == 1)
		{
			m_robber1->Draw();

			if (IsKeyDown(KEY_TAB))
			{
				m_graphEditor->Draw();
			}
			m_money->Draw();
			m_police1->Draw();
		}
	}











	EndMode2D();

	//m_robber1->Draw();//Draw player1



	EndDrawing();
}

void Application::Load()
{
	m_graph = new Graph2D();
	m_graphEditor = new Graph2DEditor(this);
	
	//Creates a variable called Keyboard1 from the keyboardbehaviour class for the first player
	auto KeyBoard1 = new KeyBoardBehaviour();

	m_tile = new TileMap();
	m_tile->Load("./assets/map.tmx");
	m_tile->SetRenderer(new TileMapRenderer());


	m_graphEditor->SetNewNodeRadius(m_tile->tileWidth + 5);


	//_________________________________________________________________________________________________________
	//First Player
	m_robber1 = new Player(this);
	m_robber1->SetFriction(0.5f);	//Calling upon the friction of the player
	m_robber1->SetPosition({ m_screenWidth * 0.25f, m_screenHeight * 0.25f });//Sets the position of the player
	m_robber1->SetEditor(m_graphEditor);

	//_________________________________________________________________________________________________________
	m_police1 = new Police(this);
	m_police1->SetFriction(0.5f);	//Calling upon the friction of the player
	m_police1->SetPosition({ m_screenWidth * 0.75f, m_screenHeight * 0.75f });//Sets the position of the player
	m_police1->SetPlayer(m_robber1);








	////How many rows and cols
	//int numRows = 4;
	//int numCols = 6;
	////Offset of these in the game.
	//float xOffset = 100;
	//float yOffset = 100;
	//float space = 50;//How far appart

	//for (int  y = 0; y < numRows; y++)
	//{
	//	for (int x = 0; x < numCols; x++)
	//	{
	//		m_graph->AddNode({
	//			x * space + xOffset,
	//			y * space + yOffset
	//			});
	//	}
	//}

	for (int y = 0; y < m_tile->rows; y++)
	{
		for (int x = 0; x < m_tile->cols; x++)
		{
			auto layer = m_tile->GetTileLayer("ground");
			auto& tileData = layer->GetTileData(x, y);
			if (tileData.globalTileId != 0)
			{
				m_graph->AddNode({
					x * (float)m_tile->tileWidth,
					y * (float)m_tile->tileHeight
				});
			}
			
		}
	}

	for (auto& node : m_graph->GetNodes())
	{
		float radiusNode = m_tile->tileWidth + 5;
		std::vector<Graph2D::Node*> closeNodes;
		m_graph->GetNearbyNodes(node->data, radiusNode, closeNodes);

		for (auto& conNode : closeNodes)
		{
			if (conNode == node)
				continue;
			float dist = Vector2Distance(node->data, conNode->data);

			m_graph->AddEdge(node, conNode, dist);
			m_graph->AddEdge(conNode, node, dist);
		}
	}

	m_graphEditor->SetGraph(m_graph);


	m_camera.target = { m_robber1->GetPosition().x + 20.0f, m_robber1->GetPosition().y + 20.0f };
	m_camera.offset = { m_screenWidth / 2.0f, m_screenHeight / 2.0f };
	m_camera.rotation = 0.0f;
	m_camera.zoom = 1.0f;



}

void Application::Unload()
{
	//Deletes the pointers
	delete m_robber1;
	m_robber1 = nullptr;
	delete m_police1;
	m_police1 = nullptr;

	delete m_graph;
	m_graph = nullptr;

	delete m_graphEditor;
	m_graphEditor = nullptr;
	delete m_tile;
}

void Application::SmoothCameraFollow(Vector2 targetPos, float dt)
{
	static float minSpeed = 30;
	static float minEffectLength = 10;
	static float fractionSpeed = 0.8f;

	m_camera.offset = { m_screenWidth / 2.0f, m_screenHeight / 2.0f };
	Vector2 diff = Vector2Subtract(targetPos, m_camera.target);
	float length = Vector2Length(diff);

	if (length > minEffectLength)
	{
		float speed = fmaxf(fractionSpeed * length, minSpeed);
		m_camera.target = Vector2Add(m_camera.target, Vector2Scale(diff, speed * dt / length));
	}

	// This logic updates the view rect
	// based on the camera position
	view.x = m_camera.target.x - (m_camera.offset.x * (1.0f / m_camera.zoom));
	view.y = m_camera.target.y - (m_camera.offset.y * (1.0f / m_camera.zoom));
	view.width = m_screenWidth * (1.0f / m_camera.zoom);
	view.height = m_screenHeight * (1.0f / m_camera.zoom);
}


Vector2 Application::GetMousePosWorld()
{
	auto mpos = ::GetMousePosition();
	return GetScreenToWorld2D(mpos, m_camera);
}

Graph2D* Application::GetGraph()
{
	return m_graph;
}

Player* Application::GetPlayer()
{
	return m_robber1;
}
