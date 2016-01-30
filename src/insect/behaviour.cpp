#include "behaviour.hpp"
#include "rosetree/rosetree.inl"
#include <algorithm>

// TODO Il faudrait revoir les comportements qu’on donne

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
{
    if (type == AphidBehaviour::Offensive)
    {
		// On va jusqu’à la fleur à détruire la plus proche
		rt.getPathToCloserWith(spawningFlower, mPath, IsAphidTarget(rt));
    }
    else
	{
		// Si le puceron est Dumb, on va au nœud le plus proche
		// Si le puceron est Coward, on va au nœud avec le moins de coccinelle
		// Dans les deux cas, on ne s’éloigne pas de plus de 6 nœuds
		ID<Flower> previousFlower = noID;
		int j = 0;
		do
			for (int j = 0 ; j < 6 ; j++)
			{
				ID<Flower> temp = spawningFlower;
				auto neighbours = rt.getNeighbours(spawningFlower);
				switch (type)
				{
					case AphidBehaviour::Dumb:
						spawningFlower = *std::min_element(neighbours.begin(), neighbours.end(), DumbCompare(rt, spawningFlower, previousFlower));
						break;
					case AphidBehaviour::Coward:
						spawningFlower = *std::min_element(neighbours.begin(), neighbours.end(), CowardCompare(rt, spawningFlower, previousFlower));
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
