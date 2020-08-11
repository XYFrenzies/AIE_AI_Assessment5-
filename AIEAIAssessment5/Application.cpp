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
		Update(dt);//UYpdate per delta Time
		Draw();
	}
	Unload();//Deletes any bits in memory not unloaded yet
}

void Application::Update(float dt)
{
	m_graphEditor->Update(dt);
	m_robber1->Update(dt);//Updates player1 per deltatime
	m_police1->Update(dt);

	SmoothCameraFollow(m_robber1->GetPosition(), dt);

}

void Application::Draw()
{
	BeginMode2D(m_camera);

	// Setting view port enables renderer
	// to only draw tiles that are visible.
	m_tile->GetRenderer()->SetView(view.x, view.y, view.width, view.height);

	// loop through each layer - invoke draw method
	for (int i = 0; i < m_tile->layers.size(); i++)
	{
		m_tile->DrawLayer(m_tile->layers[i]);

		// draw player on layer 1 (underneith walls / trees)
		if (i == 1)
		{
			m_robber1->Draw();
		}
	}

	EndMode2D();


	BeginDrawing();

	ClearBackground(BLACK);//Black background
	m_robber1->Draw();//Draw player1
	m_police1->Draw();
	m_money->Draw();
	m_graphEditor->Draw();
	EndDrawing();
}

void Application::Load()
{
	//Creates a variable called Keyboard1 from the keyboardbehaviour class for the first player
	auto KeyBoard1 = new KeyBoardBehaviour();

	m_tile = new TileMap();
//	m_tile->Load("./map.tmx");
	m_tile->SetRenderer(new TileMapRenderer());


	//_________________________________________________________________________________________________________
	//First Player
	m_robber1->SetFriction(0.5f);	//Calling upon the friction of the player
	m_robber1->SetPosition({ m_screenWidth * 0.25f, m_screenHeight * 0.25f });//Sets the position of the player
	m_police1->SetFriction(0.5f);	//Calling upon the friction of the player
	m_police1->SetPosition({ m_screenWidth * 0.75f, m_screenHeight * 0.75f });//Sets the position of the player
	m_graph = new Graph2D();

	//How many rows and cols
	int numRows = 4;
	int numCols = 6;
	//Offset of these in the game.
	float xOffset = 100;
	float yOffset = 100;
	float space = 50;//How far appart

	for (int  y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			m_graph->AddNode({
				x * space + xOffset,
				y * space + yOffset
				});
		}
	}

	for (auto node : m_graph->GetNodes())
	{
		float radiusNode = 75;
		std::vector<Graph2D::Node*> closeNodes;
		m_graph->GetNearbyNodes(node->data, radiusNode, closeNodes);

		for (auto conNode : closeNodes)
		{
			if (conNode == node)
				continue;
			float dist = Vector2Distance(node->data, conNode->data);
			
			m_graph->AddEdge(node, conNode, dist);
			m_graph->AddEdge(conNode, node, dist);
		}
	}


	m_graphEditor = new Graph2DEditor();
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