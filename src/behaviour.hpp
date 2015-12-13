#pragma once
#include <graph/node.hpp>
#include "path.hpp"

class Graph;

class Behaviour
{
    public:
        enum ID {Offensive, Dumb, Coward};
        Behaviour(Behaviour::ID, Node::ID, Graph&);
        Path & getPath();
    private:
        Branch::ID choice(Behaviour::ID, Node::ID, Node::ID, Graph&);
    private:
        Path mPath;
        Behaviour::ID mID;
};
