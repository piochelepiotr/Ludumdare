#include "graph.hpp"
#include <cmath>
#include <queue>

#include <iostream>

Graph::Graph() : m_branchId(0)
{
	addNode(Node::ID(300, 300));
	addNode(Node::ID(300, 270));
	forceNewEdge(Node::ID(300, 300), Node::ID(300, 270));
}

Branch const* Graph::getBranch(Branch::ID id) const
{
	auto it = m_branchs.find(id);
	if (it != m_branchs.end())
		return &it->second;
	else
		return nullptr;
}

Branch* Graph::getBranch(Branch::ID id)
{
	auto it = m_branchs.find(id);
	if (it != m_branchs.end())
		return &it->second;
	else
		return nullptr;
}

Node const* Graph::getNode(Node::ID id) const
{
	auto it = m_nodes.find(id);
	if (it != m_nodes.end())
		return &it->second;
	else
		return nullptr;
}

Node* Graph::getNode(Node::ID id)
{
	auto it = m_nodes.find(id);
	if (it != m_nodes.end())
		return &it->second;
	else
		return nullptr;
}

bool Graph::isCulDeSac(Branch::ID b) const
{
	
	auto it1 = m_neighbours.find(getBranch(b)->getFirstNode());
	auto it2 = m_neighbours.find(getBranch(b)->getSecondNode());
	return (it1 == m_neighbours.end() || it2 == m_neighbours.end() || it1->second.size() < 2 || it2->second.size() < 2);
}

// TODO: pour l’instant, cette fonction ne renvoie que le nombre de nœuds intermédiaires
float Graph::distance(Node::ID n1, Node::ID n2)
{
	if (m_neighbours.find(n1) == m_neighbours.end() || m_neighbours.find(n2) == m_neighbours.end())
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
			auto neighbours = m_neighbours.find(n)->second;
			for (auto pair : neighbours)
				q.push(std::make_pair(d+1, pair.first)); // TODO
		}
	}

	return std::numeric_limits<float>::infinity();
}

Node::ID Graph::addNode(Node node)
{
	NeighbourHood nh;
	Node::ID ni(node);
	m_neighbours.insert(std::make_pair(ni, nh));
	m_nodes.insert(std::make_pair(ni, node));
	return ni;
}

void Graph::addNode(Node::ID ni)
{
	NeighbourHood nh;
	m_neighbours.insert(std::make_pair(ni, nh));
	m_nodes.emplace(ni, ni);
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

Branch::ID Graph::newEdge(Node::ID n1, Node::ID n2)
{
	auto it1 = m_neighbours.find(n1), it2 = m_neighbours.find(n2);
	if (it1 != m_neighbours.end() && it2 != m_neighbours.end() && ((n1 < n2 && hasDownEdge(n1)) || (n2 < n1 && hasDownEdge(n2))))
	{
		auto id_n_it = m_branchs.emplace_hint(m_branchs.end(), std::piecewise_construct, std::forward_as_tuple(m_branchId++), std::forward_as_tuple(n1, n2));
		it1->second.insert(std::make_pair(n2, id_n_it->first));
		it2->second.insert(std::make_pair(n1, id_n_it->first));
		return id_n_it->first;
	}
	else 
		return Branch::ID(0);
}

Branch::ID Graph::forceNewEdge(Node::ID n1, Node::ID n2)
{
	auto it1 = m_neighbours.find(n1), it2 = m_neighbours.find(n2);
	if (it1 != m_neighbours.end() && it2 != m_neighbours.end())
	{
		auto id_n_it = m_branchs.emplace_hint(m_branchs.end(), std::piecewise_construct, std::forward_as_tuple(m_branchId++), std::forward_as_tuple(n1, n2));
		it1->second.insert(std::make_pair(n2, id_n_it->first));
		it2->second.insert(std::make_pair(n1, id_n_it->first));
		return id_n_it->first;
	}
	else 
		return Branch::ID(0);
}

/*
bool Graph::isItLeaf(Node::ID n1, Node::ID n2)
{
	sf::Vector2f const& p1 = n1.getPosition(), p2 = n2.getPosition();
	return std::abs(p2.y - p1.y) <= leafLimit * std::abs(p2.x - p1.x);
}
*/

bool Graph::hasDownEdge(Node::ID n) const
{
	auto it = m_neighbours.find(n);
	if (it == m_neighbours.end())
		return false;
	auto pair = it->second.begin();
	return pair != it->second.end() && pair->first < n;
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto pair : m_branchs)
	{
		pair.second.draw(target, states);
	}
}
