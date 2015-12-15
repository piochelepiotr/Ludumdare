#pragma once
#include <set>
#include <deque>
#include "graph/node.hpp"
#include "graph/branch.hpp"

#include <iostream>

class Graph;

class Path
{
	public:
		Path(Node::ID node);

		void insertBranch(Node::ID, Branch::ID);
		void addBranch(Branch::ID);
		Branch::ID frontBranch() const { return mBranchs.front(); }
		Branch::ID popBranch(Graph const& g);
		void popUntil(Node::ID n, Graph const& g)
		{
			while (!isEmpty() && mPrevNode != n)
				popBranch(g);
		}

		Node::ID getPrevNode() const { return mPrevNode; }
		bool isEmpty() const { return mBranchs.empty(); }
//		int getSize() const { return mPath.size(); }

		float length(Graph const&) const;
		

		//Branch::ID getBranchID(int n) const { return mPath[n].second; }
		//Node::ID getNodeID(int n) const { return mPath[n].first; }
		//std::pair<Node::ID, Branch::ID> getPair(int n) const { return mPath[n]; }
		//std::pair<Node::ID, Branch::ID> operator[](int n) const { return mPath[n]; }

		std::set<Node::ID> getNodes(Graph const&g) const;
		bool isCyclic(Graph const&g) const;
		void makeCyclic();

	private:
//		Node::ID getLastNodeID(Graph const&g) const;

		std::deque<Branch::ID> mBranchs;
		Node::ID mPrevNode;
};
