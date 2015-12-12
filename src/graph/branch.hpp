#pragma once
#include "node.hpp"

class Branch
{
	enum BranchType {
		None,
		RegularBranch
	};

	public:
	Branch(Node _n1, Node _n2) : n1(_n1), n2(_n2), t(), nbLadyBug(0) {}
	float getLength();
	Node getFirstNode() { return n1; }
	Node getSecondNode() { return n2; }
	int getNbLadyBug() { return nbLadyBug; }

	static Branch noneBranch;
	private:
	Branch() : n1(0, 0), n2(0, 0), t(None), nbLadyBug() {}
	Node n1;
   	Node n2;
	BranchType t;
	int nbLadyBug;
};


