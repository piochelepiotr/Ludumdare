#pragma once
#include <graph/node.hpp>
#include "path.hpp"

class Graph;

class AphidBehaviour
{
    public:
        enum ID {Offensive, Dumb, Coward};
        AphidBehaviour(AphidBehaviour::ID, Node::ID, Graph const&);
        Path const& getPath() const { return mPath; }
        Path & getPath() { return mPath; }
        Node::ID getObjective(){return mObjective;};
    private:
        Branch::ID choice(AphidBehaviour::ID, Node::ID, Node::ID, Graph const&);
        Path mPath;
        AphidBehaviour::ID mID;
        Node::ID mObjective;
};

