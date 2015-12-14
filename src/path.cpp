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


int Path::size() {
  return mPath.size();;
}

std::set<Node::ID> Path::getNodes(Graph const& g) const {
  std::set<Node::ID> result;
  result.insert(getLastNodeID(g));
  for (auto &i : mPath) {
    result.insert(i.first);
  }
  return result;
}

Node::ID Path::getLastNodeID(Graph const&g) const{
  std::pair<Node::ID, Branch::ID> lastPair = mPath[mPath.size() - 1];
  Branch const& lastBranch = g[lastPair.second];
  return lastBranch.getOtherNode(lastPair.first);
}

bool Path::isCyclic(Graph const&g) const {
  return mPath[0].first == getLastNodeID(g);
}

void Path::makeCyclic(Graph const&g) {
  int size = mPath.size();
  mPath.push_back(std::pair<Node::ID, Branch::ID>(getLastNodeID(g), mPath[size - 1].second));
  for (int i = 1; i < size; i++) {
    mPath.push_back(std::pair<Node::ID, Branch::ID>(mPath[size - i].first, mPath[size - 1 - i].second));
  }
}

float Path::length(Graph const& graph) const
{
    float mLength = 0;
    for (auto& stuff : mPath)
    {
        mLength += graph[stuff.second].getLength();
    }
    return mLength;
}
