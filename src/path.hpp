#pragma once

class Path
{
    public:
        Path();
        void addBranch(Node::ID, Branch::ID, float len);
        float length() { return m_length; }
        Branch::ID getBranchID(int n);  
    private:
        std::vector<std::pair<Node::ID, Branch::ID> > mPath;
		float m_length;
};
