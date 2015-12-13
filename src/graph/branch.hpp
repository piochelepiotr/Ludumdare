#pragma once

#include <algorithm>

#include "node.hpp"
#include "../math/spline.hpp"

class Graph;

class Branch
{
	public:
	enum BranchType {
		None,
		RegularBranch
	};
	typedef unsigned int ID;

	Branch(Node::ID _n1, Node::ID _n2, Graph& graph);
	Branch();

	float getLength() { return ss.getLength(); }
	Node::ID getFirstNode() const { return n1; }
	Node::ID getSecondNode() const { return n2; }
	Node::ID getOtherNode(Node::ID node) const
	{ return n1 == node ? n2 : n1; }

	int getNbLadyBug() { return nbLadyBug; }
        Spline getSpline(); //this is a Spline, not a SplineShape!

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	static Branch noneBranch;
	private:

	Node n1;
   	Node n2;
	BranchType t;
	int nbLadyBug;
	SplineShape ss;
};
