#pragma once
#include <graph/node.hpp>
#include "path.hpp"

class Graph;

class AphidBehaviour
{
    public:
        enum ID {Offensive, Dumb, Coward};
        AphidBehaviour(AphidBehaviour::ID, Node::ID, Graph&);
        Path & getPath();
    private:
        Branch::ID choice(AphidBehaviour::ID, Node::ID, Node::ID, Graph&);
        Path mPath;
        AphidBehaviour::ID mID;
};
