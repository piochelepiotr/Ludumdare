#pragma once

class Path
{
    public:
        Path();
        void addBranch(node::ID, branch::ID);
        float length();
    private:
        std::vector<(Node::ID, Branch::ID)> mPath;
};
