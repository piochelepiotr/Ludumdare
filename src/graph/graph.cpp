#include "graph.hpp"
#include <cmath>
#include <queue>

#include <iostream>

Graph::Graph() : m_branchId(0)
{
	addNode(Node::ID(300, 300));
	addNode(Node::ID(300, 170));
	forceNewEdge(Node::ID(300, 300), Node::ID(300, 170));
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
	return (it1 == m_neighbours.end() || it2 == m_neighbours.end() || it1->second.size() < 2 || it2->second.size() < 2 || (*this)[getBranch(b)->getFirstNode()].m_t != Texture::ID::RegularNode || (*this)[getBranch(b)->getSecondNode()].m_t != Texture::ID::RegularNode);
}

/*
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

*/

void Graph::makePath()
{
	int n = m_nodes.size();
	std::vector<std::pair<float, Branch::ID> > ligne(n, std::make_pair(std::numeric_limits<float>::infinity(), 0));
	std::vector<std::vector<std::pair<float, Branch::ID> > > matrix(n, ligne);
	std::map<Node::ID, int> toInt;
	std::map<int, Node::ID> toID;

	int i = 0; //, j = 0, k = 0;
	for (auto pair : m_nodes)
	{
		toInt.insert(std::make_pair(pair.first, i));
		toID.insert(std::make_pair(i++, pair.first));
	}

	i = 0;
	for (auto node_neighbours : m_neighbours)
	{
		Node::ID const& previousNode(sf::Vector2f(std::numeric_limits<float>::infinity(), 0));
		float previousDist(0);

		for (auto node_branch : node_neighbours.second)
		{
			Node::ID const& node2 = node_branch.first;
			Branch::ID branch = node_branch.second;
			float dist = m_branchs.find(branch)->second.getLength();
			if (!(node2 == previousNode) || dist < previousDist)
				matrix[i][toInt[node2]] = std::make_pair(dist, branch);
		}
		i++;
	}

	for (int k = 0 ; k < n ; k++)
	{
		for (i = 0 ; i < n ; i++)
		{
			for (int j = 0 ; j < n ; j++)
			{
				auto &a = matrix[i][j];
				float d = matrix[i][k].first + matrix[k][j].first;
				if (a.first > d)
					a = std::make_pair(d, matrix[i][k].second);
			}
		}
	}

	m_paths.clear();
	for (i = 0 ; i < n ; i++)
		for (int j = 0 ; j < n ; j++)
			m_paths.insert(std::make_pair(std::make_pair(toID.find(i)->second, toID.find(j)->second), matrix[i][j]));
}

Path Graph::getPath(Node::ID n1, Node::ID n2)
{
	Path p;
	auto it = m_paths.find(std::make_pair(n1, n2));
	Node::ID node = n1;
	Branch::ID branch = it->second.second;
	Branch& graph_branch = (*this)[branch];
	while (it != m_paths.end() && graph_branch.getOtherNode(node) != n2)
	{
		p.addBranch(node, branch);
		it = m_paths.find(std::make_pair(graph_branch.getOtherNode(node), n2));
		node = graph_branch.getOtherNode(node);
		branch = it->second.second;
		graph_branch = (*this)[branch];
	}
	p.addBranch(node, branch);
	return p;
}

float Graph::getDist(Node::ID n1, Node::ID n2) {
  return m_paths[std::make_pair(n1, n2)].first;
}


Node::ID Graph::addNode(Node node)
{
	NeighbourHood nh;
	Node::ID ni(node);
	m_neighbours.insert(std::make_pair(ni, nh));
	m_nodes.insert(std::make_pair(ni, node));
	makePath();
	return ni;
}

void Graph::addNode(Node::ID ni)
{
	NeighbourHood nh;
	m_neighbours.insert(std::make_pair(ni, nh));
	m_nodes.emplace(ni, ni);
	makePath();
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
	if (it1 != m_neighbours.end()
			 && it2 != m_neighbours.end()
//			 && (*this)[n1].getType() == Node::Type::RegularNode
//			 && (*this)[n2].getType() == Node::Type::RegularNode
//	TODO		 && ((n1 < n2 && hasDownEdge(n1)) || (n2 < n1 && hasDownEdge(n2)))
			)
	{
		auto id_n_it = m_branchs.emplace_hint(m_branchs.end(), std::piecewise_construct, std::forward_as_tuple(m_branchId++), std::forward_as_tuple(n1, n2));
		it1->second.insert(std::make_pair(n2, id_n_it->first));
		it2->second.insert(std::make_pair(n1, id_n_it->first));
		makePath();
		return id_n_it->first;
	}
	else
	{
		std::cout << 4 << std::endl;
		return Branch::ID(0);
	}
}

Branch::ID Graph::forceNewEdge(Node::ID n1, Node::ID n2)
{
	auto it1 = m_neighbours.find(n1), it2 = m_neighbours.find(n2);
	if (it1 != m_neighbours.end() && it2 != m_neighbours.end())
	{
		auto id_n_it = m_branchs.emplace_hint(m_branchs.end(), std::piecewise_construct, std::forward_as_tuple(m_branchId++), std::forward_as_tuple(n1, n2));
		it1->second.insert(std::make_pair(n2, id_n_it->first));
		it2->second.insert(std::make_pair(n1, id_n_it->first));
		makePath();
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

	for (auto pair : m_nodes)
	{
		pair.second.draw(target, states);
	}

}
