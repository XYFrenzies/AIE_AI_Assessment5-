#pragma once
#include "Graph.h"
#include "raymath.h"
class Graph2D : public Graph<Vector2, float>
{
public:

	Graph2D();
	virtual ~Graph2D();

	void GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes);

	bool PathFinder(Node* startNode, std::function<bool(Node*)>isGoalNode, std::list<Node*>& out_path);

	bool PathFinder(Node* startNode, Node* endNode, std::list<Node*>& out_path);

protected:
private:



};

