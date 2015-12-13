#pragma once

#include <algorithm>

#include "node.hpp"
#include "../math/spline.hpp"

class Branch
{
	public:
	enum BranchType {
		None,
		RegularBranch
	};
	typedef unsigned int ID;

	Branch(Node _n1, Node _n2);

	float getLength() { return ss.getLength(); };
	Node::ID const getFirstNode() const { return n1; }
	Node::ID getFirstNode() { return n1; }
	Node::ID const getSecondNode() const { return n2; }
	Node::ID getSecondNode() { return n2; }
	int getNbLadyBug() { return nbLadyBug; }
        Spline getSpline(); //this is a Spline, not a SplineShape!

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	static Branch noneBranch;
	private:
	static Branch getNoneBranch(Node _n1, Node _n2) { Branch b(_n1, _n2); b.t = None; return b; }

	Node n1;
   	Node n2;
	BranchType t;
	int nbLadyBug;
	SplineShape ss;
};
