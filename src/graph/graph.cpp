#include "graph.hpp"
#include <cmath>

Graph::Graph()
{
	addNode(Node(0, 0));
	addNode(Node(0, 10));
	forceNewEdge(Node(0, 0), Node(0, 10));
}

void Graph::addNode(Node node)
{
	std::multimap<Node, EdgeType> newMap;
	m_nodes.insert(std::make_pair(node, newMap));
}

EdgeType Graph::newEdge(Node n1, Node n2)
{
	EdgeType t = NONE;
	sf::Vector2f const& p1 = n1.getPosition(), p2 = n2.getPosition();
	if (isItLeaf(n1, n2))
	{
		if (hasDownEdge(n1) && hasDownEdge(n2))
			t = LEAF;
	}
	else if (n1 < n2 && hasDownEdge(n1) || n2 < n1 && hasDownEdge(n2))
		t = BRANCH;

	auto it1 = m_nodes.find(n1), it2 = m_nodes.find(n2);
	if (it1 != m_nodes.end() && it2 != m_nodes.end() && t != NONE)
	{
		it1->second.insert(std::make_pair(n2, t));
		it2->second.insert(std::make_pair(n1, t));
		return t;
	}
	else
		return NONE;
}

EdgeType Graph::forceNewEdge(Node n1, Node n2)
{
	EdgeType t = NONE;
	sf::Vector2f const& p1 = n1.getPosition(), p2 = n2.getPosition();
	if (isItLeaf(n1, n2))
		t = LEAF;
	else
		t = BRANCH;

	auto it1 = m_nodes.find(n1), it2 = m_nodes.find(n2);
	if (it1 != m_nodes.end() && it2 != m_nodes.end())
	{
		it1->second.insert(std::make_pair(n2, t));
		it2->second.insert(std::make_pair(n1, t));
		return t;
	}
	else
		return NONE;
}



bool Graph::isItLeaf(Node n1, Node n2)
{
	sf::Vector2f const& p1 = n1.getPosition(), p2 = n2.getPosition();
	return std::abs(p2.y - p1.y) <= leafLimit * std::abs(p2.x - p1.x);
}

bool Graph::hasDownEdge(Node n) const
{
	auto it = m_nodes.find(n);
	if (it == m_nodes.end())
		return false;
	for (auto pair : it->second)
	{
		if (n < pair.first)
			return false;
		else if (pair.second == BRANCH)
			return true;
	}
	return false;
}

