#pragma once
#include <vector>

template <class TNodeData, class TEdgeData>
class Graph
{
public:
	struct Edge;
	struct Node;

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
protected:

	std::vector<Node*> m_nodes;

private:
};
