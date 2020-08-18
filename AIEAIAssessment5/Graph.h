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
		float hScore;
		float fScore;
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
protected:

	std::vector<Node*> m_nodes;

private:
};
