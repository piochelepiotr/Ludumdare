#pragma once
#include <map>
#include <set>
#include "node.hpp"
#include "branch.hpp"
#include "../path.hpp"

float constexpr leafLimit = 0.3f;

class Graph
{
	typedef std::multimap<Node::ID, Branch::ID> NeighbourHood;
	typedef NeighbourHood multimap;

	public:
	Graph(); // TODO: Pour l’instant, cette fonction est un peu bidon
	//float distance(Node::ID n1, Node::ID n2);
	Node::ID addNode(Node n);
	void addNode(Node::ID n);
	Branch::ID newEdge(Node::ID n1, Node::ID n2);
	// static bool isItLeaf(Node::ID n1, Node::ID n2);
	bool hasDownEdge(Node::ID n) const;
	bool isCulDeSac(Branch::ID b) const;

	Branch const* getBranch(Branch::ID id) const;
	Branch* getBranch(Branch::ID id);
	Node const* getNode(Node::ID id) const;
	Node* getNode(Node::ID id);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Path getPath(Node::ID n1, Node::ID n2);

	private:

	void makePath();

	Branch::ID forceNewEdge(Node::ID n1, Node::ID n2);
	std::map<Node::ID, NeighbourHood> m_neighbours;

	std::map<Node::ID, Node> m_nodes;

	Branch::ID m_branchId;
	std::map<Branch::ID, Branch> m_branchs;

	std::map<std::pair<Node::ID, Node::ID>, std::pair<float, Branch::ID> > m_paths;
};
