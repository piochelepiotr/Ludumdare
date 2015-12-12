#pragma once
#include "node.hpp"
#include "graph.hpp"

class Behaviour:
{
    enum ID {Offensive, Dumb, Coward};
    public:
        Behaviour(Behaviour::ID, Node, Graph*);
    private:
        Branch choice(Behaviour::ID, Node, Node, Graph*);
    private:
        std::vector<(Node, Branch)> mPath;
        Behaviour::ID mID;
}
