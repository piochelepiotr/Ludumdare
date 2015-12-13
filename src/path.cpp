#include "path.hpp"

Path::Path()
: mPath()
{
}

void Path::addBranch(Node::ID node, Branch::ID branch, float len)
{
  mPath.push_back(std::make_pair(node, branch));
	m_length += len;
}


Branch::ID Path::getBranchID(int n) {
  return mPath[n].second;
}
