#include "behaviour.hpp"
//#include "graph/graph.hpp"
#include <iostream>
#include <limits>
#include "rosetree/flower.hpp"
#include "rosetree/branch.hpp"

// Predicat pour la fonction getPathToCloserIf,
// qui renvoie true si ça peut être la cible d’un puceron
class IsAphidTarget
{
	public:
	IsAphidTarget(RoseTree const& rt) : mRoseTree(rt) {};
	bool operator () (ID<Flower> f)
	{
		Flower::Type type = mRoseTree[f].getType();
		return type == Flower::Type::RegularFlower
			|| type == Flower::Type::LadybugFlower;
	}
	RoseTree const& mRoseTree;
};


// Prédicat de comparaison pour trouver le chemin des Dumbs
class DumbCompare
{
	public:
	DumbCompare(RoseTree const& rt, ID<Flower> currentFlower, ID<Flower> previousFlower) :
		mRt(rt), mCurrentFlower(currentFlower), mPreviousFlower(previousFlower) {}
	bool operator () (ID<Flower> f1, ID<Flower> f2)
	{
		if (f1 == mPreviousFlower)
			return false;
		if (f2 == mPreviousFlower)
			return true;
		Branch const& b1 = mRt.getBranch(mCurrentFlower, f1);
		Branch const& b2 = mRt.getBranch(mCurrentFlower, f2);
		return b1.getLength() < b2.getLength();
	}

	RoseTree const& mRt;
	ID<Flower> mCurrentFlower;
	ID<Flower> mPreviousFlower;
};


// Prédicat de comparaison pour trouver le chemin des Cowards
class CowardCompare
{
	public:
	CowardCompare(RoseTree const& rt, ID<Flower> currentFlower, ID<Flower> previousFlower) :
		mRt(rt), mCurrentFlower(currentFlower), mPreviousFlower(previousFlower) {}
	bool operator () (ID<Flower> f1, ID<Flower> f2)
	{
		if (f1 == mPreviousFlower)
			return false;
		if (f2 == mPreviousFlower)
			return true;
		Branch const& b1 = mRt.getBranch(mCurrentFlower, f1);
		Branch const& b2 = mRt.getBranch(mCurrentFlower, f2);
		return std::make_pair(b1.getLadybugNumber(), b1.getLength())
			< std::make_pair(b2.getLadybugNumber(), b2.getLength());
	}

	RoseTree const& mRt;
	ID<Flower> mCurrentFlower;
	ID<Flower> mPreviousFlower;
};




AphidBehaviour::AphidBehaviour(AphidBehaviour::Type type, ID<Flower> spawningFlower, RoseTree const& rt)
: mPath(spawningFlower)
, mType(type)
//, mObjective(0.f,0.f)
{
    if (type == AphidBehaviour::Offensive) // On va jusqu’à la fleur à détruire la plus proche
    {
		/*
        float minLength = std::numeric_limits<float>::infinity();
		ID<Flower> min_flowerID = noID;
        for (ID<Flower> flowerID : rt.getFlowers())
        {
			Flower const& flower = rt[flowerID];
            if (flower.getType() == Flower::Type::RegularFlower || flower.getType() == Flower::Type::LadybugFlower)
            {
                float length = rt.getDistance(spawningFlower, flowerID);
                if (length < minLength)
                {
                    //mObjective = node;
                    minLength = length;
					min_flowerID = flowerID;
                }
            }
        }
		if (min_flowerID != noID)
			rt.getPath(spwaningFlower, min_flowerID, mPath);
		*/

		rt.getPathToCloserWith(spawningFlower, mPath, IsAphidTarget(rt));
    }
	// Si le puceron est Dumb, on va au nœud le plus proche
	// Si le puceron est Coward, on va au nœud avec le moins de coccinelle
    else
    {
		// TODO What the fuck R we doin' here ?
		/*
        ID<Branch> spawningBranch = graph.getNeighbours(spawningNode).begin()->second;
        Branch graph_spawningBranch = graph[spawningBranch];
        mPath.addBranch(spawningBranch);
        Node::ID newNode(0.f, 0.f);
        if (!(graph_spawningBranch.getFirstNode() == spawningNode))
            newNode = graph_spawningBranch.getFirstNode();
        else
            newNode = graph_spawningBranch.getSecondNode();

		Node::ID previousNode = spawningNode;

        int j = 0;
        while (graph[newNode].getType() == Texture::ID::RegularNode && j<5)
        {
            Branch::ID newBranch = choice(id, newNode, previousNode, graph);
            mPath.addBranch(newBranch);
            previousNode = newNode;
            if (!(graph[newBranch].getFirstNode() == newNode))
			{
                newNode = graph[newBranch].getFirstNode();
			}
            else
			{
                newNode = graph[newBranch].getSecondNode();
			}
			j++;
        }
		*/
		ID<Flower> previousFlower = noID;
		int j = 0;
		do
		for (int j = 0 ; j < 6  ; j++)
		{
			ID<Flower> temp = spawningFlower;
			auto neighbours = rt.getNeighbours(spawningFlower);
			switch (type)
			{
				case AphidBehaviour::Dumb:
					spawningFlower = *min_element(neighbours.begin(), neighbours.end(), DumbCompare(rt, spawningFlower, previousFlower));
					break;
				case AphidBehaviour::Coward:
					spawningFlower = *min_element(neighbours.begin(), neighbours.end(), CowardCompare(rt, spawningFlower, previousFlower));
					break;
				default:
					break;
			}
			previousFlower = temp;
			mPath.addNode(spawningFlower);
			j++;
		}
		while (j < 6 && rt[spawningFlower].getType() == Flower::Type::RegularFlower);

    }
}


/*
ID<Flower> AphidBehaviour::choice(AphidBehaviour::Type type, ID<Flower> actualFlower, ID<Flower> previousFlower, RoseTree const& rt)
{
	auto neighbours = graph.getNeighbours(actualNode);
	Branch::ID branchChosen = neighbours.begin()->second;
	Branch const* graph_branchChosen = graph.getBranch(branchChosen);

	for (auto& stuff: neighbours)
	{
		Branch::ID branch = stuff.second;
		Branch const* graph_branch = graph.getBranch(branch);

		if (!graph.isCulDeSac(branch) && graph_branch->getFirstNode() != previousNode && graph_branch->getSecondNode() != previousNode)
		{

			if ((type == AphidBehaviour::Coward &&
						(graph_branch->getNbLadyBug() < graph_branchChosen->getNbLadyBug()
						 || (graph_branch->getNbLadyBug() == graph_branchChosen->getNbLadyBug()
							 && graph_branch->getLength() < graph_branchChosen->getLength())))
					|| (type == AphidBehaviour::Dumb && graph_branch->getLength() < graph_branchChosen->getLength()))
			{
				branchChosen = branch;
				graph_branchChosen = graph_branch;
			}
		}
	}

	return branchChosen;
}
*/
