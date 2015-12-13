#include "branch.hpp"
#include <iostream>
#include "graph.hpp"

Branch Branch::noneBranch = Branch();

Branch::Branch(Node::ID _n1, Node::ID _n2, Graph& graph) :
	n1(_n1),
	n2(_n2),
	t(),
	nbLadyBug(0),
	ss(
			3.0f,
			30,
			std::min(_n1, _n2).id,
			std::max(_n1, _n2).id,
			sf::Vector2f(0, -100),
			sf::Vector2f(0, -100)
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
	std::cout << "b : " << this << std::endl;
	sf::sleep(sf::milliseconds(100));
	ss.draw(target, states);
}

Spline Branch::getSpline() {
  return ss.getSpline();
}
