#include "Graph2DEditor.h"
#include <iostream>
#include "Graph2D.h"
Graph2DEditor::Graph2DEditor()
{
}

Graph2DEditor::~Graph2DEditor()
{
}

void Graph2DEditor::Update(float deltaTime)
{
}

void Graph2DEditor::Draw()
{
	if (this == NULL)
		return;
	//Draw all connections
	for (auto node : m_graph->GetNodes())
	{
		for (auto connection : node->connections)
		{
			DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, GRAY);
		}
	}
	//Draw all Nodes
	for (auto node : m_graph->GetNodes())
	{
		DrawCircle(node->data.x, node->data.y, 8, LIGHTGRAY);
		DrawCircleLines(node->data.x, node->data.y, 8, LIGHTGRAY);
	}



}

Graph2D* Graph2DEditor::GetGraph()
{
	return m_graph;
}

void Graph2DEditor::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}
