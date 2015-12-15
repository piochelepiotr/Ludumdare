#include "path.hpp"
#include "graph/graph.hpp"

Path::Path(Node::ID node) : mBranchs(), mPrevNode(node)
{
}

void Path::insertBranch(Node::ID node, Branch::ID branch) {
	mPrevNode = node;
	mBranchs.push_front(branch);
}

void Path::addBranch(Branch::ID branch) {
	mBranchs.push_back(branch);
}

Branch::ID Path::popBranch(Graph const& g)
{
	Branch::ID tempBranch = mBranchs.front();
	mPrevNode = g[tempBranch].getOtherNode(mPrevNode);
	mBranchs.pop_front();
	return tempBranch;
}


std::set<Node::ID> Path::getNodes(Graph const& g) const {
	std::set<Node::ID> result;
	Node::ID prev = mPrevNode;
	for (Branch::ID b : mBranchs) {
		result.insert(prev);
		prev = g[b].getOtherNode(prev);
	}
	result.insert(prev);
	return result;
}

/*Node::ID Path::getLastNodeID(Graph const&g) const{
	Node::ID prev = mPrevNode;
	for (Branch::ID b : mBranchs)
		prev = g[b].getOtherNode(prev);
	return prev;
}*/

bool Path::isCyclic(Graph const&g) const {
	Node::ID prev = mPrevNode;
	for (Branch::ID b : mBranchs)
		prev = g[b].getOtherNode(prev);
	return mPrevNode == prev;
}

void Path::makeCyclic() {
	std::deque<Branch::ID> result;
	for (auto it = mBranchs.rbegin() ; it != mBranchs.rend() ; it++)
		result.push_front(*it), result.push_back(*it);
	mBranchs = std::move(result);
}

float Path::length(Graph const& graph) const
{
	float length = 0;
	for (Branch::ID b : mBranchs)
		length += graph[b].getLength();

	return length;
}
