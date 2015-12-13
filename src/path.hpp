#pragma once

class Path
{
    public:
        Path();
        void addBranch(Node::ID, Branch::ID);
        float length();
        Branch::ID getBranchID(int n);
    private:
        std::vector<(Node::ID, Branch::ID)> mPath;
};
