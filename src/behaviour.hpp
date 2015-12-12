#pragma once
#include <graph/node.hpp>
#include <graph/graph.hpp>

class Behaviour
{
    enum ID {Offensive, Dumb, Coward};
    public:
        Behaviour(Behaviour::ID, Node, Graph*);
    private:
        Branch choice(Behaviour::ID, Node, Node, Graph*);
    private:
        std::vector<(Node, Branch)> mPath;
        Behaviour::ID mID;
};
