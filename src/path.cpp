#include "path.hpp"

Path::Path()
: mPath()
{
}

void Path:addBranch(Node::ID node, Branch::ID branch, float len)
{
    mPath.push_back((node, branch));
	m_length += d;
}
