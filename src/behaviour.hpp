#pragma once
#include <graph/node.hpp>
#include <graph/graph.hpp>
#include "path.hpp"

class Behaviour
{
    public:
        enum ID {Offensive, Dumb, Coward};
        Behaviour(Behaviour::ID, Node, Graph*);
    private:
        Branch::ID choice(Behaviour::ID, Node, Node, Graph*);
    private:
        Path mPath;
        Behaviour::ID mID;
};
