#pragma once
#include "graph/node.hpp"
#include "graph/branch.hpp"

class Graph;

class Path
{
    public:
        Path();
        void addBranch(Node::ID, Branch::ID);
        float length(Graph&);
        Branch::ID getBranchID(int n);

    private:
        std::vector<std::pair<Node::ID, Branch::ID> > mPath;
		float m_length;
};
