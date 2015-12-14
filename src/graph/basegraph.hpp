#pragma once
#include "graph.hpp"
#include <iostream>
#include "utils.hpp"

class BaseGraph
{
public:
    BaseGraph();
    BaseGraph(std::string name);
    Graph makeGraph();
    Node::ID nextNode(Graph &g);
    Graph & getBaseGraph() const { return mGraph; }
    
private:
    Graph mGraph;
};