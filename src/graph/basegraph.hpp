#pragma once
#include "graph.hpp"
#include <iostream>

class BaseGraph
{
public:
    BaseGraph();
    BaseGraph(std::string name);
    Graph makeGraph();
    Node::ID nextNode(Graph g);
    Graph & getBaseGraph() const { return mGraph; }
    
private:
    Graph mGraph;
};