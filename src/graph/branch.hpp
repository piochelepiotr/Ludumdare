#pragma once

#include <algorithm>

#include "node.hpp"
#include "math/spline.hpp"

class Branch
{
	enum BranchType {
		None,
		RegularBranch
	};

	public:
	Branch(Node _n1, Node _n2) : n1(_n1), n2(_n2), t(), nbLadyBug(0), ss(3.0f, 20, std::min(_n1, _n2).getPosition(), std::max(_n1, _n2).getPosition(), sf::Vector2f(0, -100), sf::Vector2f(0, -100)) {}
	Branch getNoneBranch(Node _n1, Node _n2) { Branch b(_n1, _n2); b.t = None; return b; }
	float getLength();
	Node getFirstNode() { return n1; }
	Node getSecondNode() { return n2; }
	int getNbLadyBug() { return nbLadyBug; }

	static Branch noneBranch;
	private:
	Node n1;
   	Node n2;
	BranchType t;
	int nbLadyBug;

	SplineShape ss;
	
};


