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
	
	//Draws line of the line
	if (!m_path.empty())
	{
		for (int i = 0; i < m_path.size() - 1; i++)
		{
			DrawLineEx(m_path[i], m_path[i + 1], 6, RED);
		}

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
