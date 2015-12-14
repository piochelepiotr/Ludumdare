#pragma once
#include <set>
#include "graph/node.hpp"
#include "graph/branch.hpp"

class Graph;

class Path
{
public:
  Path();
  void insertBranch(Node::ID, Branch::ID);
  void addBranch(Node::ID, Branch::ID);
  float length(Graph const&) const;

  Branch::ID getBranchID(int n) const { return mPath[n].second; }
  Node::ID getNodeID(int n) const { return mPath[n].first; }
  std::pair<Node::ID, Branch::ID> getPair(int n) const { return mPath[n]; }
  std::pair<Node::ID, Branch::ID> operator[](int n) const { return mPath[n]; }

  int getSize() const { return mPath.size(); }
  Node::ID getLastNodeID(Graph const&g) const;
  int size();
  std::set<Node::ID> getNodes(Graph const&g) const;
  bool isCyclic(Graph const&g) const;
  void makeCyclic(Graph const&g);
private:
  std::vector<std::pair<Node::ID, Branch::ID> > mPath;
  float m_length;
};
