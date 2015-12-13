#pragma once
#include "graph/node.hpp"
#include "graph/branch.hpp"


class Path
{
    public:
        Path();
        void addBranch(Node::ID, Branch::ID, float len);
        float length() { return m_length; }
    private:
        std::vector<std::pair<Node::ID, Branch::ID> > mPath;
		float m_length;
};
