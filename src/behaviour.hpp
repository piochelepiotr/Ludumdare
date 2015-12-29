#pragma once
//#include <graph/node.hpp>
//#include "path.hpp"
#include "id.hpp"
#include "rosetree/rosetree.hpp"
#include "rosetree/path.hpp"

class Flower;
class Branch;

class AphidBehaviour
{
    public:
        enum Type {Offensive, Dumb, Coward};
        AphidBehaviour(AphidBehaviour::Type, ID<Flower>, RoseTree const&);
        Path<Flower> const& getPath() const { return mPath; }
        Path<Flower> & getPath() { return mPath; }
        //ID<Flower> getObjective(){ return mObjective; }
    private:
        //ID<Branch> choice(AphidBehaviour::Type, ID<Flower>, ID<Flower>, Graph<Flower, Branch> const&);
        Path<Flower> mPath;
        AphidBehaviour::Type mType;
//        ID<Flower> mObjective;
};

