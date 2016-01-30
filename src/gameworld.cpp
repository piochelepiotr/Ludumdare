#include "gameworld.inl"
#include "insect/insect.inl"
#include "insectanchorlistener.hpp"
#include "anchor/anchorpool.hpp"

GameWorld::GameWorld(Mode mode) :
	mLadybugs(),
	mAphids(),
    mTotalCapacity(3),
    mRemainingCapacity(mTotalCapacity),
	mMode(mode)
{
}

GameWorld::~GameWorld()
{
	for (auto ladybug : mLadybugs)
		delete ladybug;

	for (auto aphid : mAphids)
		delete aphid;
}


Aphid& GameWorld::spawnAphid(ID<Flower> flower)
{
	mAphids.push_back(new Aphid(mRoseTree, flower, AphidBehaviour::Offensive));
	return *mAphids.back();
}

Ladybug& GameWorld::spawnLadybug(ID<Flower> flower, Ladybug::Type type)
{
	Ladybug& ladybug = *(new Ladybug(mRoseTree, flower, type));
	mLadybugs.push_back(&ladybug);
	// TODO Doit-on donner un chemin par défaut aux Ladybug ?
	// TODO Cela dépend du type de Ladybug, non ?
	// TODO Peut-être attendre un clic ici pour que Ladybug apparaîsse…
	// Pour l’instant, on va lui donner un chemin par défaut :
	//		Elle va jusqu’à un nœud voisin de la fleur et elle revient;
	//		Si il n’y a pas de voisin, elle reste là…
	auto& neighbours = mRoseTree.getNeighbours(flower);
	if (!neighbours.empty())
	{
		Path<Flower> p(flower);
		p.addNode(*neighbours.begin());
		ladybug.redefinePath(p);
	}
	return ladybug;
}

void GameWorld::update(sf::Time dt)
{
	// Si on est en train d’éditer tout ça, pas besoin de tout ça
	if (mMode == EditMode)
		return;

	// Commençons par mettre à jour les Ladybugs
	for (auto ladybug : mLadybugs)
	{
		// Si ladybug n’est pas déjà en train de manger,
		// elle mange un Aphid assez proche sur sa branche
		if (ladybug->isEating())
			ladybug->decreaseEatingTime(dt);
		else
		{
			ladybug->move(dt);

			// TODO C’est toujours pas la bonne solution
			if (!ladybug->isObjectiveReached())
			{
				ID<Branch> currentBranch = ladybug->getBranch();
				float currentPos = ladybug->getPos();

				for (auto it = mAphids.begin() ; it != mAphids.end() ; ++it)
				{
					Aphid& aphid = **it;
					// TODO Il faudrait changer ces conditions
					if (aphid.getBranch() == currentBranch &&
							std::abs(currentPos - aphid.getPos()) < 0.1f)
					{
						ladybug->eatAnAphid(aphid);
						delete &aphid;
						mAphids.erase(it);
						break;
					}
				}
			}
		}
	}

	// On s’occupe des Aphids. Si l’un d’entre eux atteint une fleur,
	// alors il se suicide, et enlève un point à la fleur.
	// Comme il est plus facile d’ajouter en fin de tableau que de supprimer,
	// on crée un nouveau tableau auquel on n'ajoute tous ceux qu’on enlève pas
	// (tordu, n’est-il pas ? c’est pourquoi TODO Changer ça (ou pas))
	std::vector<Aphid*> newAphids;
	for (auto aphid : mAphids)
	{
		aphid->move(dt);
		if (aphid->isObjectiveReached())
		{
			Flower& flower = mRoseTree[aphid->getPrevFlower()];
			// TODO Est-ce ce qu’il faut faire ?
			if (!flower.loseOnePoint())
				flower.becomeNode();
			delete aphid;
		}
		else
		{
			newAphids.push_back(aphid);
		}
	}
	mAphids = std::move(newAphids);

	// Et maintenant, les fleurs. Il faut juste libérer, délivrer les insectes
	// qui peuvent l’être.
	for (auto& ID_n_flower : mRoseTree.getFlowers())
	{
		Flower& flower = ID_n_flower.second;
		if (flower.update(dt))
		{
			switch(flower.getType())
			{
				case Flower::AphidFlower:
					spawnAphid(ID_n_flower.first);
					flower.setTimeLeft(sf::seconds(0.9f)); // TODO Ne pas le fixer à 2
					break;
				case Flower::LadybugFlower:
					spawnLadybug(ID_n_flower.first, Ladybug::BlackLadybug);
					flower.becomeNode(); // Doit-on faire ça ?
					break;
				default:
					break;
			}
		}
	}
}


ID<Branch> GameWorld::addBranch(ID<Flower> f1, ID<Flower> f2)
{
	if (getRemainingCapacity() > 0 || mMode == EditMode)
	{
		ID<Branch> id = mRoseTree.addBranch(f1, f2);
		if (id)
			useCapacity(1);
		return id;
	}
	else
		return noID;
}
