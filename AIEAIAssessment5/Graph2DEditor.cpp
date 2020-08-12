#include "Graph2DEditor.h"
#include <iostream>
#include "Graph2D.h"
#include <list>
#include "Application.h"

Graph2DEditor::Graph2DEditor(Application *app) : m_graph()
{
	m_app = app;
}

Graph2DEditor::~Graph2DEditor()
{
}

void Graph2DEditor::Update(float deltaTime)
{
	if (IsMouseButtonPressed(1))
	{

		auto mousePos = m_app->GetMousePosWorld();

		// get the first node that we click on.
		std::vector<Graph2D::Node*> neibouringNodes;
		m_graph->GetNearbyNodes(mousePos, 8, neibouringNodes);
		if (neibouringNodes.empty() == false)
		{
			if (m_startNode == nullptr)
				m_startNode = neibouringNodes[0];
			else if (m_endNode == nullptr)
				m_endNode = neibouringNodes[0];
			else { m_startNode = neibouringNodes[0]; m_endNode = nullptr; }
			// Begin Search
			// call the FindPath method
			if (m_endNode != nullptr)
			{
				auto isGoalNode = [this](Graph2D::Node* node) {
					return node == m_endNode;
				};

				std::list<Graph2D::Node*> path; // stores the path
				if (m_graph->PathFinder(m_startNode, isGoalNode, path))
				{
					m_path.clear();
					for (auto nodePath : path)
					{
						m_path.push_back(nodePath->data);
					}

				}
			}
		}
	}


	if (IsMouseButtonPressed(0))
	{
		auto mousePos = m_app->GetMousePosWorld();

		std::vector<Graph2D::Node*> nearNodes;
		m_graph->GetNearbyNodes(mousePos, radiusNode, nearNodes);
		for (auto nearbyNodes : nearNodes)
		{
			float dist = Vector2Distance(mousePos, nearbyNodes->data);
			if (dist < radDist)
				return;
		}
		auto newNode = m_graph->AddNode(mousePos);


		for (auto& nearbyNodes : nearNodes)
		{
			float dist = Vector2Distance(newNode->data, nearbyNodes->data);
			m_graph->AddEdge(newNode, nearbyNodes, dist);
			m_graph->AddEdge(nearbyNodes, newNode, dist);
		}

	}
}

void Graph2DEditor::Draw()
{
	//Draw all connections
	for (auto& node : m_graph->GetNodes())
	{
		for (auto connection : node->connections)
		{
			DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, GRAY);
		}
	}
	//Draw all Nodes
	for (auto& node : m_graph->GetNodes())
	{
		DrawRectangle(node->data.x - 3, node->data.y - 3, 6, 6, LIGHTGRAY);
		// DrawCircle(node->data.x, node->data.y, 8, LIGHTGRAY);
		// DrawCircleLines(node->data.x, node->data.y, 8, LIGHTGRAY);
	}

	//This is to draw the start and end points of when the nodes have been selected.
	if (m_startNode != nullptr)
	{
		DrawCircle(m_startNode->data.x, m_startNode->data.y, 4, ORANGE);
	}
	if (m_endNode != nullptr)
	{
		DrawCircle(m_endNode->data.x, m_endNode->data.y, 4, GREEN);
	}
	



	//Draws a "Preview" node where the mouse is
	auto mousePos = m_app->GetMousePosWorld();
	DrawCircle(mousePos.x, mousePos.y, 6, LIGHTGRAY);

	if (!m_path.empty())
	{
		for (int i = 0; i < m_path.size() - 1; i++)
		{
			DrawLineEx(m_path[i], m_path[i + 1], 6, RED);
		}

	}


	//Draws all the links to the nearby nodes.
	std::vector<Graph2D::Node*> nearNodes;
	m_graph->GetNearbyNodes(mousePos, radiusNode, nearNodes);

	for (auto& nearbyNodes : nearNodes)
	{
		DrawLine(mousePos.x, mousePos.y, nearbyNodes->data.x, nearbyNodes->data.y, LIGHTGRAY);
	}

}

void Graph2DEditor::SetNewNodeRadius(float r)
{
	radiusNode = r;
}

Graph2D* Graph2DEditor::GetGraph()
{
	return m_graph;
}

void Graph2DEditor::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}
