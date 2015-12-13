#pragma once
#include <unordered_set>
#include "graph/node.hpp"
#include "graph/branch.hpp"

class Graph;

class Path
{
public:
  Path();
  void addBranch(Node::ID, Branch::ID);
  float length(Graph&);
  Branch::ID getBranchID(int n);
  Node::ID getLastNodeID(Graph &g);
  std::unordered_set<Node::ID> getNodes(Graph &g);
  bool isCyclic(Graph &g);
  void makeCyclic(Graph &g);
private:
  std::vector<std::pair<Node::ID, Branch::ID> > mPath;
  float m_length;
};
