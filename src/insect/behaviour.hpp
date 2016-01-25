#pragma once
#include "utils/id.hpp"
#include "rosetree/path.hpp"

class Flower;
class Branch;
class RoseTree;

class AphidBehaviour
{
    public:
        enum Type {Offensive, Dumb, Coward};
        AphidBehaviour(AphidBehaviour::Type, ID<Flower>, RoseTree const&);
        Path<Flower> const& getPath() const { return mPath; }
        Path<Flower> & getPath() { return mPath; }
    private:
        Path<Flower> mPath;
        AphidBehaviour::Type mType;
};

