#include "path.hpp"
#include "graph/graph.hpp"

Path::Path()
: mPath()
{
}

void Path::addBranch(Node::ID node, Branch::ID branch)
{
    mPath.push_back(std::make_pair(node, branch));
}


Branch::ID Path::getBranchID(int n) {
  return mPath[n].second;
}

float Path::length(Graph& graph)
{
    float mLength = 0;
    for (auto stuff : mPath)
    {
        mLength += graph[stuff.second].getLength();
    }
    return mLength;
}
