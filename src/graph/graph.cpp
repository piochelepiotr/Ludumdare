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

bool Graph::isCulDeSac(Branch b) const
{
	auto it1 = m_nodes.find(b.getFirstNode());
	auto it2 = m_nodes.find(b.getSecondNode());
	return (it1 == m_nodes.end() || it2 == m_nodes.end() || it1->second.size() < 2 || it2->second.size() < 2);
}

// TODO: pour l’instant, cette fonction ne renvoie que le nombre de nœuds intermédiaires
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

Branch const* Graph::newEdge(Node n1, Node n2)
{
	auto it1 = m_nodes.find(n1), it2 = m_nodes.find(n2);
	if (it1 != m_nodes.end() && it2 != m_nodes.end() && ((n1 < n2 && hasDownEdge(n1)) || (n2 < n1 && hasDownEdge(n2))))
	{
		auto id_n_it = m_branchs.emplace_hint(m_branchs.end(), std::piecewise_construct, std::forward_as_tuple(m_branchId++), std::forward_as_tuple(n1, n2));
		it1->second.insert(std::make_pair(n2, id_n_it->first));
		it2->second.insert(std::make_pair(n1, id_n_it->first));
		return &id_n_it->second;
	}
	else 
		return nullptr;
}

Branch const* Graph::forceNewEdge(Node n1, Node n2)
{
	auto it1 = m_nodes.find(n1), it2 = m_nodes.find(n2);
	if (it1 != m_nodes.end() && it2 != m_nodes.end())
	{
		auto id_n_it = m_branchs.emplace_hint(m_branchs.end(), std::piecewise_construct, std::forward_as_tuple(m_branchId++), std::forward_as_tuple(n1, n2));
		it1->second.insert(std::make_pair(n2, id_n_it->first));
		it2->second.insert(std::make_pair(n1, id_n_it->first));
		return &id_n_it->second;
	}
	else 
		return nullptr;
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
	auto pair = it->second.begin();
	return pair != it->second.end() && pair->first < n;
}

