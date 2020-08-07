#pragma once
#include "raymath.h"
#include "Graph2D.h"
class Graph2D;

class Graph2DEditor
{
public:

	Graph2DEditor();
	~Graph2DEditor();

	void Update(float deltaTime);
	void Draw();

	Graph2D* GetGraph();
	void SetGraph(Graph2D* graph);

protected:

	Graph2D* m_graph;
	float radiusNode = 75;
	float radDist = 30;
	Graph2D::Node* m_startNode = nullptr;
	Graph2D::Node* m_endNode = nullptr;
	std::vector<Vector2> m_path; // stores the path

private:
};

