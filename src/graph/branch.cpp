#include "branch.hpp"
#include <iostream>
#include "graph.hpp"

Branch Branch::noneBranch = Branch();

Branch::Branch(Node::ID _n1, Node::ID _n2, Graph& graph) :
	n1(std::min(_n1, _n2)),
	n2(std::max(_n1, _n2)),
	t(),
	nbLadyBug(0),
	ss(
			3.0f,
			30,
			n1.getPosition(),
			n2.getPosition(),
			graph.getDerivative(n1, n2.getPosition() - n1.getPosition()),
			graph.getDerivative(n2, n2.getPosition() - n1.getPosition())
	  )
{}


Branch::Branch() :
	n1(sf::Vector2f(0, 0)),
	n2(n1),
	t(None),
	nbLadyBug(0),
	ss(0, 0, n1.getPosition(), n1.getPosition(), n1.getPosition(), n1.getPosition())
{}


void Branch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ss.draw(target, states);
}
