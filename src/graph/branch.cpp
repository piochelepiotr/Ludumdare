#include "branch.hpp"

Branch Branch::noneBranch = getNoneBranch(Node::ID(2, 3), Node::ID(4, 4));


Branch::Branch(Node _n1, Node _n2) :
	n1(_n1),
	n2(_n2),
	t(),
	nbLadyBug(0),
	ss(
			6.0f,
			30,
			std::min(_n1, _n2).getPosition(),
			std::max(_n1, _n2).getPosition(),
			sf::Vector2f(0, -100),
			sf::Vector2f(0, -100)
	  )
{}



void Branch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ss.draw(target, states);
}

Spline Branch::getSpline() {
  return ss.getSpline();
}
