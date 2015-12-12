#pragma once
#include <map>
#include <set>
#include "node.hpp"
#include "branch.hpp"

float constexpr leafLimit = 0.3f;

class Graph
{
	typedef std::multimap<Node, Branch> NeighbourHood;
	typedef NeighbourHood multimap;
	public:
	Graph(); // TODO: Pour l’instant, cette fonction est un peu bidon
	float distance(Node n1, Node n2);

	void addNode(Node n);
	Branch const& newEdge(Node n1, Node n2);
	static bool isItLeaf(Node n1, Node n2);
	bool hasDownEdge(Node n) const;

	bool isCulDeSac(Branch b) const;

	private:
	Branch const& forceNewEdge(Node n1, Node n2);
	std::map<Node, NeighbourHood> m_nodes;
};

