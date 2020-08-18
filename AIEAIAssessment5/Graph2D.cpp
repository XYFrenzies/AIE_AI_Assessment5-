#include "Graph2D.h"

Graph2D::Graph2D()
{
}

Graph2D::~Graph2D()
{
}

void Graph2D::GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes)
{
	out_nodes.clear();//This is to delete the nodes so that it can be updated properly per frame in the police gameobject.
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
		PathFindNode* currentNode = stack.back();//Sets the current node to the last in the stack

		stack.pop_back();//Pops that last node off the stack
		visited.push_back(currentNode);//pushes that popped off node or the currentNode to the visited list.

		if (isGoalNode(currentNode->graphNode))//If the currentNode is the goalNode (Where the location of the path needs to go)
		{
			PathFindNode* current = currentNode;
			while (current != nullptr)//This will loop through the entire path
			{
				out_path.push_front(current->graphNode);
				current = current->parent;
			}
			return true;
		}
		for (Edge& edges : currentNode->graphNode->connections)//Loops through every edge
		{
			auto pathFindNode = IfNodesExist(edges.to);//Creates a pathNode
			//If the path to find is nullptr
			if (pathFindNode == nullptr)
			{
				PathFindNode* pathFindNode = new PathFindNode();//Creates an instance of the path in memory
				pathFindNode->gScore = currentNode->gScore + edges.data;//The gScore of the node is equal to the currentNodes gScore + the data of the edge
				pathFindNode->parent = currentNode;//The parent is then set ot currentNode
				pathFindNode->graphNode = edges.to;//The graphNode is equal to the edges
				stack.push_back(pathFindNode);//Pushes the new pathfindNode to the end of the stack

			}
			else//If the pathfindNode is not nullptr
			{
				if (pathFindNode->gScore > currentNode->gScore + edges.data)//If the gScore is larger than the currentNode's gScore
				{
					pathFindNode->parent = currentNode;//The parent is not the currentNode
					pathFindNode->gScore = currentNode->gScore + edges.data;//The gScore is now
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

bool Graph2D::PathFinder(Node* startNode, Node* endNode, std::list<Node*>& out_path)
{

	std::list<PathFindNode*> stack;
	std::vector<PathFindNode*> alreadyProcessed;
	//landa function to find is node already exists in either stack list or alreadyProcessed list
	auto GetNodeInLists = [&](Node* nodeToFind) -> PathFindNode*
	{
		for (auto& n : stack)
			if (n->graphNode == nodeToFind)
				return n;
		for (auto& n : alreadyProcessed)
			if (n->graphNode == nodeToFind)
				return n;
		return nullptr;
	};
	//create startNode values
	PathFindNode* pFNode = new PathFindNode();
	pFNode->gScore = 0.0f;
	pFNode->hScore = 0.0f;
	pFNode->fScore = 0.0f;
	pFNode->parent = nullptr;
	pFNode->graphNode = startNode;
	//push start node onto stack
	stack.push_back(pFNode);
	//while stack isnt empty
	while (!stack.empty())
	{
		//set current node to last node in stack list
		PathFindNode* currentNode = stack.back();
		//remove the last node from the stack list
		stack.pop_back();
		//put current node into alreadyProcessed list
		alreadyProcessed.push_back(currentNode);

		//if current node is the goal node store the path it used inside of out_path node
		if (endNode == currentNode->graphNode)
		{
			PathFindNode* current = currentNode;
			while (current != nullptr)
			{
				out_path.push_front(current->graphNode);
				current = current->parent;
			}
			return true;
		}
		//for each edge in current nodes connections
		for (Edge& edge : currentNode->graphNode->connections)
		{
			//checks if current nodes connection is in stack list or stack list
			auto pFNodeChild = GetNodeInLists(edge.to);
			float gScore = currentNode->gScore + edge.data;
			// TODO: optimise this. // Distance Squared from node to goalNode.
			float hScore = Vector2Distance(edge.to->data, endNode->data) * Vector2Distance(edge.to->data, endNode->data);
			// Final Score.
			float fScore = gScore + hScore;
			//if node wasnt in list 
			if (pFNodeChild == nullptr)
			{
				//create a new node
				PathFindNode* pFNodeChild = new PathFindNode();
				//add the currents node score to the PFNodeChild score
				pFNodeChild->gScore = gScore;
				pFNodeChild->hScore = hScore;
				pFNodeChild->fScore = fScore;
				//make PFNodeChilds parent = current node
				pFNodeChild->parent = currentNode;
				pFNodeChild->graphNode = edge.to;
				stack.push_back(pFNodeChild);
			}
			//node was found in stack list or visited list
			else
			{
				if (pFNodeChild->fScore > fScore)
				{
					pFNodeChild->parent = currentNode;
					pFNodeChild->gScore = gScore;
					pFNodeChild->hScore = hScore;
					pFNodeChild->fScore = fScore;
				}
			}
		}
		//sort stack so the lowest score node is at end of list
		stack.sort([&](PathFindNode* a, PathFindNode* b)
			{
				return a->fScore > b->fScore;
			});
	}
	return false;
}



