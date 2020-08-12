#pragma once
#include <vector>
#include <functional>
#include <list>

template <class TNodeData, class TEdgeData>
class Graph
{
public:
	struct Edge;
	struct Node;

	struct PathFindNode
	{
		Node* graphNode;
		PathFindNode* parent;
		float gScore;
	};
	struct Node
	{
		TNodeData data;
		std::vector<Edge> connections;
	};
	struct Edge
	{
		Node* to;
		TEdgeData data;
	};

	//======================================================================
	//Constructor
	//======================================================================
	Graph() {}
	//======================================================================
	//Deconstructor
	//======================================================================
	virtual ~Graph()
	{
		for (auto node : m_nodes)
		{
			delete node;
		}
		m_nodes.clear();
	}
	void DeleteNode() 
	{
		for (auto node : m_nodes)
		{
			delete node;
		}
		m_nodes.clear();
	}
	//======================================================================
	//AddNode
	//======================================================================
	Node* AddNode(const TNodeData& data)
	{
		Node* node = new Node();
		node->data = data;
		m_nodes.push_back(node);
		return node;
	}
	//======================================================================
	//AddEdge
	//======================================================================
	void AddEdge(Node* nodeA, Node* nodeB, const TEdgeData& data)
	{
		nodeA->connections.push_back({ nodeB, data });
	}
	//======================================================================
	//GetNode
	//======================================================================
	const std::vector<Node*>& GetNodes()
	{
		return m_nodes;
	}

	Node* ForEachBFS(Node* startNode, std::function<bool(Node * n)> process)
	{

		std::vector<Node*> stack;
		std::vector<Node*> visited;

		if (startNode == nullptr)
			startNode = m_nodes[0];

		stack.push_back(startNode);
		while (!stack.empty())
		{
			Node* stackData = stack.back();
			stack.pop_back();
			visited.push_back(stackData);
			process(stackData);

			for (Edge& edges : stackData->connections)
			{
				auto stackVal = std::find(stack.begin(), stack.end(), edges.to);
				auto visitVal = std::find(visited.begin(), visited.end(), edges.to);

				if (stackVal != stack.end() || visitVal != visited.end())
					continue;
				stack.insert(stack.begin(), edges.to);
			}
		}
		//ToDo, implement pseudo code;
		return nullptr;
	}

	Node* ForEachDFS(Node* startNode, std::function<bool(Node * n)> process)
	{

		std::vector<Node*> stack;
		std::vector<Node*> visited;

		if (startNode == nullptr)
			startNode = m_nodes[0];

		stack.push_back(startNode);
		while (!stack.empty())
		{
			Node* stackData = stack.back();
			stack.pop_back();
			visited.push_back(stackData);
			process(stackData);

			for (Edge& edges : stackData->connections)
			{
				auto stackVal = std::find(stack.begin(), stack.end(), edges.to);
				auto visitVal = std::find(visited.begin(), visited.end(), edges.to);

				if (stackVal != stack.end() || visitVal != visited.end())
					continue;
				stack.push_back(edges.to);
			}
		}
		//ToDo, implement pseudo code;
		return nullptr;
	}

	//bool BeginSearch(Node* startNode, std::function<bool(Node*)>isGoalNode, std::list<Node*> out_path)
	//{

	//	std::list<PathFindNode*> stack;
	//	std::list<PathFindNode*> visited;

	//	//A lambda function to check for any existing nodes within visited or stack
	//	auto IfNodesExist = [&](Node* findingNode)->PathFindNode*
	//	{
	//		for (auto& node : stack, visited)
	//			if (node->graphNode == findingNode)
	//				return node;
	//		return nullptr;
	//	};

	//	if (startNode == nullptr || isGoalNode == nullptr)
	//		return false;

	//	//Create a new instance of a node with the first node
	//	PathFindNode* newPath = new PathFindNode();
	//	newPath->graphNode = startNode;
	//	newPath->gScore = 0.0f;
	//	newPath->parent = nullptr;
	//	//Pushes the starting node to the list
	//	stack.push_back(newPath);

	//	while (!stack.empty())
	//	{
	//		//Sort the stack by the g.score

	//		stack.sort([](PathFindNode* a, PathFindNode* b)
	//			{
	//				a->gScore > b->gScore;
	//			});

	//		PathFindNode* currentNode = stack.back();

	//		stack.pop_back();
	//		visited.push_back(currentNode);

	//		if (isGoalNode(currentNode->graphNode))
	//		{
	//			while (currentNode != nullptr)
	//			{
	//				out_path.push_front(currentNode->graphNode);
	//				currentNode = currentNode->parent;
	//			}
	//			return true;
	//		}
	//		for (Edge& edges : currentNode->graphNode->connections)
	//		{

	//			for (auto node : visited, stack)
	//			{
	//				if (node->graphNode == edges.to && node->graphNode == nullptr)
	//				{
	//					PathFindNode* pFChild = new PathFindNode();
	//					pFChild->gScore = currentNode->gScore + edges.data;
	//					pFChild->parent = currentNode;
	//					pFChild->graphNode = edges.to;
	//					stack.push_back(pFChild);

	//				}
	//				else
	//				{
	//					if (node->gScore > currentNode->gScore + edges.data)
	//					{
	//						node->parent = currentNode;
	//						node->gScore = currentNode->gScore + edges.data;
	//					}
	//				}
	//			}

	//		}
	//	}
	//	return false;

	//}


protected:

	std::vector<Node*> m_nodes;

private:
};
