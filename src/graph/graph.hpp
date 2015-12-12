#pragma once
#include <map>
#include <set>
#include "node.hpp"

float constexpr leafLimit = 0.3f;

enum EdgeType
{
	NONE,
	BRANCH,
	LEAF
};

class Node;

class Graph
{
	typedef std::multimap<Node, EdgeType> multimap;
	public:
	Graph(); // TODO: Pour l’instant, cette fonction est un peu bidon
	float distance(Node n1, Node n2);

	void addNode(Node node);
	EdgeType newEdge(Node n1, Node n2);
	static bool isItLeaf(Node n1, Node n2);
	bool hasDownEdge(Node n) const;
	private:
	EdgeType forceNewEdge(Node n1, Node n2);
	std::map<Node, multimap> m_nodes;

	private:
};

