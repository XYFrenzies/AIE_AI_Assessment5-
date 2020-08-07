#include "Graph2D.h"

Graph2D::Graph2D()
{
}

Graph2D::~Graph2D()
{
}

void Graph2D::GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes)
{
	for (auto node : m_nodes)
	{
		float dist = Vector2Distance(position, node->data);
		if (dist < radius)
		{
			out_nodes.push_back(node);
		}
	}
}

bool Graph2D::PathFinder(Node* startNode, std::function<bool(Node*)>isGoalNode, std::list<Node*>& out_path)
{
	std::list<PathFindNode*> stack;
	std::vector<PathFindNode*> visited;

	//A lambda function to check for any existing nodes within visited or stack
	auto IfNodesExist = [&](Node* findingNode)->PathFindNode*
	{
		for (auto& node : stack)
			if (node->graphNode == findingNode)
				return node;
		for (auto& node : visited)
			if (node->graphNode == findingNode)
				return node;
		return nullptr;
	};

	//Create a new instance of a node with the first node
	PathFindNode* newPath = new PathFindNode();
	newPath->graphNode = startNode;
	newPath->gScore = 0.0f;
	newPath->parent = nullptr;
	//Pushes the starting node to the list
	stack.push_back(newPath);

	while (!stack.empty())
	{


		PathFindNode* currentNode = stack.back();

		stack.pop_back();
		visited.push_back(currentNode);

		if (isGoalNode(currentNode->graphNode))
		{
			PathFindNode* current = currentNode;
			while (current != nullptr)
			{
				out_path.push_front(current->graphNode);
				current = current->parent;
			}
			return true;
		}
		for (Edge& edges : currentNode->graphNode->connections)
		{

			auto pathFindNode = IfNodesExist(edges.to);

			if (pathFindNode == nullptr)
			{
				PathFindNode* pathFindNode = new PathFindNode();
				pathFindNode->gScore = currentNode->gScore + edges.data;
				pathFindNode->parent = currentNode;
				pathFindNode->graphNode = edges.to;
				stack.push_back(pathFindNode);

			}
			else
			{
				if (pathFindNode->gScore > currentNode->gScore + edges.data)
				{
					pathFindNode->parent = currentNode;
					pathFindNode->gScore = currentNode->gScore + edges.data;
				}
			}
		}
		//Sort the stack by the g.score

		stack.sort([](PathFindNode* a, PathFindNode* b)
			{
				return a->gScore > b->gScore;
			});

	}
	return false;
}


