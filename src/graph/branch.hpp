#pragma once

class Branch
{
	enum BranchType {
		None,
		RegularBranch
	};

	public:
	Branch(Node _n1, Node _n2) : n1(_n1), n2(_n2), t() {};
	float getLength();
	Node getFirstNode() { return n1; }
	Node getSecondNode() { return n2; }
	int getNbLadyBux() { return nbLadyBug; }

	private:
	Node n1;
   	Node n2;
	BranchType t;
	int nbLadyBug;
};
