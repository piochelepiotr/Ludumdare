#include "path.hpp"
#include "graph/graph.hpp"

Path::Path()
: mPath()
{
}

void Path::insertBranch(Node::ID node, Branch::ID branch) {
  mPath.insert(mPath.begin(), std::make_pair(node, branch));
}

void Path::addBranch(Node::ID node, Branch::ID branch)
{
    mPath.push_back(std::make_pair(node, branch));
}


Branch::ID Path::getBranchID(int n) {
  return mPath[n].second;
}

Node::ID Path::getNodeID(int n) {
  return mPath[n].first;
}

int Path::size() {
  return mPath.size();;
}

std::set<Node::ID> Path::getNodes(Graph &g) {
  std::set<Node::ID> result;
  result.insert(getLastNodeID(g));
  for (auto &i : mPath) {
    result.insert(i.first);
  }
  return result;
}

Node::ID Path::getLastNodeID(Graph &g) {
  std::pair<Node::ID, Branch::ID> lastPair = mPath[mPath.size() - 1];
  Branch *lastBranch = g.getBranch(lastPair.second);
  if (lastBranch->getFirstNode() == lastPair.first)
    return lastBranch->getSecondNode();
  else
    return lastBranch->getFirstNode();
}

bool Path::isCyclic(Graph &g) {
  return mPath[0].first == getLastNodeID(g);
}

void Path::makeCyclic(Graph &g) {
  int size = mPath.size();
  mPath.push_back(std::pair<Node::ID, Branch::ID>(getLastNodeID(g), mPath[size - 1].second));
  for (int i = 1; i < size; i++) {
    mPath.push_back(std::pair<Node::ID, Branch::ID>(mPath[size - i].first, mPath[size - 1 - i].second));
  }
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
