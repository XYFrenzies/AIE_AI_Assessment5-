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
	//m_player1->Update(dt);//Updates player1 per deltatime
	m_graphEditor->Update(dt);

}

void Application::Draw()
{
	BeginDrawing();

	ClearBackground(BLACK);//Black background
	//m_player1->Draw();//Draw player1
	m_graphEditor->Draw();
	EndDrawing();
}

void Application::Load()
{
	//Creates a variable called Keyboard1 from the keyboardbehaviour class for the first player
	auto KeyBoard1 = new KeyBoardBehaviour();
	//_________________________________________________________________________________________________________
	//First Player
	//m_player1->SetFriction(0.5f);	//Calling upon the friction of the player
	//m_player1->SetPosition({ m_screenWidth * 0.25f, m_screenHeight * 0.25f });//Sets the position of the player
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





}

void Application::Unload()
{
	//Deletes the pointers
	//delete m_player1;
	//m_player1 = nullptr;
	delete m_graph;
	m_graph = nullptr;

	delete m_graphEditor;
	m_graphEditor = nullptr;
}

void Application::TestGraph()
{

	Graph<char, int> graph;
	auto a = graph.AddNode('A');
	auto b = graph.AddNode('B');
	auto c = graph.AddNode('C');
	auto d = graph.AddNode('D');
	auto e = graph.AddNode('E');
	auto f = graph.AddNode('F');
	auto g = graph.AddNode('G');
	auto h = graph.AddNode('H');
	auto i = graph.AddNode('I');
	graph.AddEdge(a, b, 0); graph.AddEdge(b, a, 0);     // AB
	graph.AddEdge(a, i, 0); graph.AddEdge(i, a, 0);     // AS
	graph.AddEdge(c, i, 0); graph.AddEdge(i, c, 0);     // SC
	graph.AddEdge(g, i, 0); graph.AddEdge(i, g, 0);     // SG
	graph.AddEdge(f, c, 0); graph.AddEdge(c, f, 0);     // FC
	graph.AddEdge(f, g, 0); graph.AddEdge(g, f, 0);     // FG
	graph.AddEdge(d, c, 0); graph.AddEdge(c, d, 0);     // CD
	graph.AddEdge(c, e, 0); graph.AddEdge(e, c, 0);     // CE
	graph.AddEdge(g, h, 0); graph.AddEdge(h, g, 0);     // GH
	graph.AddEdge(e, h, 0); graph.AddEdge(h, e, 0);     // EH
	// This is a BFS traversal.
	// if the method returns true, the traversal will stop
	// if the method returns false, the traversal will continue
	//graph.ForEachBFS(nullptr, [](Graph<char, int>::Node* node) {
	//	std::cout << node->data << std::endl;
	//	return false;
	//	});
	//std::cout << "------------" << std::endl;
	////std::cout << "------------" << std::endl;
	//// This is a BFS traversal.
	//// if the method returns true, the traversal will stop
	//// if the method returns false, the traversal will continue
	//graph.ForEachDFS(f, [](Graph<char, int>::Node* node) {
	//	std::cout << node->data << std::endl;
	//	return false;
	//	});
	//std::list<Graph2D::Node*> path; // stores the path
	//auto isGoalNode = [this](Graph2D::Node* node) {
	//	return node == m_endNode;
	//};


}
