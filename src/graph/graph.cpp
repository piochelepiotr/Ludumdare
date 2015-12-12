#include "graph.hpp"
#include <cmath>
#include <queue>

#include <iostream>

Graph::Graph()
{
	addNode(Node(0, 0));
	addNode(Node(0, 10));
	forceNewEdge(Node(0, 0), Node(0, 10));
}

// TODO: pour l’instant, cette fonction ne renvoie que le nombre de nœuds intermédiaires
// TODO: De plus, on ne fait pas de vérification de EdgeType
float Graph::distance(Node n1, Node n2)
{
	if (m_nodes.find(n1) == m_nodes.end() || m_nodes.find(n2) == m_nodes.end())
		return std::numeric_limits<float>::infinity();


	std::priority_queue<std::pair<float, Node> > q;
	std::set<Node> s;

	q.push(std::make_pair(0., n1));
	while (!q.empty())
	{
		std::pair<float, Node> pair = q.top();
		float d = pair.first;
		Node n = pair.second;
		q.pop();
		if (n == n2)
			return d;

		if (s.find(n) == s.end())
		{
			s.insert(n);
			auto neighbours = m_nodes.find(n)->second;
			for (auto pair : neighbours)
				q.push(std::make_pair(d+1, pair.first)); // TODO
		}
	}

	return std::numeric_limits<float>::infinity();
}

void Graph::addNode(Node node)
{
	NeighbourHood nh;
	m_nodes.insert(std::make_pair(node, nh));
}

/*
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
*/

Branch const& Graph::newEdge(Node n1, Node n2)
{
	auto it1 = m_nodes.find(n1), it2 = m_nodes.find(n2);
	sf::Vector2f const& p1 = n1.getPosition(), p2 = n2.getPosition();
	if (it1 != m_nodes.end() && it2 != m_nodes.end() && hasDownEdge(n1) || hasDownEdge(n2))
	{
		Branch b(n1, n2, ;
		it1->second.insert(std::make_pair(n2, t));
		it2->second.insert(std::make_pair(n1, t));
		return  
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

