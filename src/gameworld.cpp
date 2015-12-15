#include "gameworld.hpp"
#include <iostream>
#include <insectanchorlistener.hpp>
//GameWorld::GameWorld()
//{

//}

//GameWord

	GameWorld::GameWorld(sf::Sprite redLdb, sf::Sprite redBlackLdb, sf::Sprite blackLdb, sf::Sprite aphid, sf::Sprite backGround, Graph& g, AnchorPool& anchor)
	: mGraph(&g)
	, mLadyBugs()
	, mAphids()
	, mFlowers()
	, mBackGround(backGround)
    , mInsectSprites()
    , mCapacity(3)
    , mUsedCapacity(0)
    , mAnchorPool(&anchor)
{
	redLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::RedLadybug)] = redLdb;
	redBlackLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::RedBlackLadybug)] = redBlackLdb;
	blackLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::BlackLadybug)] = blackLdb;
	aphid.setOrigin(50.0f, 75.0f);
	mInsectSprites[static_cast<int>(Insect::Aphid)] = aphid;

	for (auto& stuff : getGraph())
	{
		Node::ID node = stuff.first;
		switch (g[node].getType())
		{
			case Texture::ID::AphidFlower:
				mFlowers.push_back(new Flower(node, 5, sf::seconds(0), Texture::ID::AphidFlower));
				break;
			case Texture::ID::Flower:
				mFlowers.push_back(new Flower(node, 5, sf::seconds(60), Texture::ID::Flower));
				break;
			case Texture::ID::LadyBugFlower:
				mFlowers.push_back(new Flower(node, 5, sf::seconds(3), Texture::ID::LadyBugFlower));
				break;
			default:
				break;
		}
	}
}

GameWorld::~GameWorld()
{

}


void GameWorld::render(sf::RenderTarget& target)
{
	target.draw(mBackGround);
	getGraph().draw(target, sf::RenderStates::Default);
	for (auto ldb : mLadyBugs) {
		ldb->draw(target, getGraph(), mInsectSprites[static_cast<size_t>(ldb->getType())]);
	}
	for (auto &apd : mAphids) {
		apd->draw(target, getGraph(), mInsectSprites[static_cast<size_t>(Insect::Aphid)]);
	}
}

Insect* GameWorld::spawnInsect(Insect::type type, Node::ID node)
{
	if (type == Insect::Aphid)
	{
		mAphids.push_back(new Aphid(AphidBehaviour::Offensive, node, getGraph()));
		return *mAphids.end();
	} else {
		mLadyBugs.push_back(new LadyBug(type, node, getGraph()));
		mAnchorPool->addAnchor<InsectAnchorListener>(AnchorItem(20.f), *mLadyBugs.back());
		return * --mLadyBugs.end();
	}
}

Node::ID GameWorld::spawnNode(NodeType type, sf::Vector2f position)
{
	// TODO FIXME
	return Node::ID(position);
}


void GameWorld::update(sf::Time dt)
{
  for (auto &ldb : mLadyBugs)
  {
    if (!ldb->getBusy())
        ldb->move(dt.asSeconds(), getGraph());
    ldb->setBusyTime(ldb->getBusyTime() + dt);
    if (ldb->getBusyTime() > sf::seconds(3))
    {
        ldb->setBusy(false);
        ldb->setBusyTime(sf::seconds(0));
    }
    for (unsigned int i=0; i<mAphids.size(); ++i)
    {
        Aphid *apd = mAphids[i];
        if (ldb->getBranch() == apd->getBranch())
        {
            if (ldb->getPos(getGraph()) < apd->getPos(getGraph())+0.1
				&& ldb->getPos(getGraph()) > apd->getPos(getGraph())-0.1
				&& !ldb->getBusy())
            {
                ldb->setBusy(true);
                mAphids.erase(mAphids.begin()+i);
            }
        }
    }
  }
  for (unsigned int i=0; i<mAphids.size(); ++i)
  {
    Aphid *apd = mAphids[i];
    apd->move(dt.asSeconds(), getGraph());
    if (apd->isObjectiveReached())
    {
        Node::ID node = apd->getPrevNode();
        for (unsigned int j=0; j<mFlowers.size(); ++j)
        {
            Flower *flower = mFlowers[j];
            if (Node::ID(*flower) == node)
            {
                if (flower->loseOnePoint())
                {
                    mFlowers.erase(mFlowers.begin()+i);
                }
            }
        }
        mAphids.erase(mAphids.begin()+i);
    }
  }
  for (auto flower : mFlowers) {
    bool isReady = flower->update(dt);
    if (isReady)
    {
        Node::Type type = flower->getType();
        if (type == Texture::ID::AphidFlower)
        {
            if (flower->getCurrentTime() > sf::seconds(4))
            {
                spawnInsect(Insect::Aphid, Node::ID(*flower));
                flower->setCurrentTime(sf::seconds(0));
            }
        }
        if (type == Texture::ID::LadyBugFlower)
        {
			Node::ID node = *flower;
            LadyBug* ladybug = static_cast<LadyBug*>(spawnInsect(Insect::BlackLadybug, node));

			// TODO Doit-on donner un chemin par défaut aux LadyBug ?
			// TODO Peut-être attendre un clic ici pour que LadyBug apparaîsse…
			// Pour l’instant, on va lui donner un chemin par défaut :
			//		Elle va jusqu’à un nœud voisin de la fleur et elle revient;
			//		Si il n’y a pas de voisin, elle reste là…
			auto& nh = mGraph->getNeighbours(node);
			if (nh.size() > 0)
			{
				Path p(node);
				p.addBranch(nh.begin()->second);
				ladybug->redefinePath(p, *mGraph);
			}

            flower->becameNode();
        }
    }
  }
}


