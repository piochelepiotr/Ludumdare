#pragma once
#include <map>
#include <set>
#include "node.hpp"

float leafLimit = 0.3f;

enum EdgeType
{
	NONE,
	BRANCH,
	LEAF
};

class Node;

class Graph
{
	public:
	Graph(); // TODO: Pour l’instant, cette fonction est un peu bidon
	double distance(Node n1, Node n2);

	void addNode(Node node);
	EdgeType newEdge(Node n1, Node n2);
	static bool isItLeaf(Node n1, Node n2);
	bool hasDownEdge(Node n) const;
	private:
	std::map<Node, std::multimap<Node, EdgeType> > m_nodes;
	EdgeType forceNewEdge(Node n1, Node n2);
};

