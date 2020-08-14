#include "Application.h"

#include "Behaviour.h"
#include "KeyBoardBehaviour.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"


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
	m_robber->Update(dt);//Updates player1 per deltatime
	m_graphEditor->Update(dt);
}

void Application::Draw()
{
	BeginDrawing();

	ClearBackground(BLACK);//Black background
	m_robber->Draw();//Draw player1
	m_graphEditor->Draw();
	EndDrawing();
}

void Application::Load()
{
	//Creates a variable called Keyboard1 from the keyboardbehaviour class for the first player
	auto KeyBoard1 = new KeyBoardBehaviour();
	//_________________________________________________________________________________________________________
	//First Player
	m_robber->SetFriction(0.5f);	//Calling upon the friction of the player
	m_robber->SetPosition({ m_screenWidth * 0.25f, m_screenHeight * 0.25f });//Sets the position of the player
}

void Application::Unload()
{
	//Deletes the pointers
	delete m_robber;
	m_robber = nullptr;
	delete m_graph;
	m_graph = nullptr;

	delete m_graphEditor;
	m_graphEditor = nullptr;
}
