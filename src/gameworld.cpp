#include "gameworld.hpp"
#include <iostream>
#include <insectanchorlistener.hpp>
#include "rosetree/flower.hpp"
//GameWorld::GameWorld()
//{

//}

//GameWord

GameWorld::GameWorld(/*sf::Sprite redLdb, sf::Sprite redBlackLdb, sf::Sprite blackLdb, sf::Sprite aphid, sf::Sprite backGround, */RoseTree& rt, AnchorPool& anchor, State::Context& context)
	: mRoseTree(rt)
	, mLadyBugs()
	, mAphids()
//	, mFlowers()
	, mBackGround(/*backGround*/)
    , mInsectSprites()
    , mCapacity(3)
    , mUsedCapacity(0)
    , mAnchorPool(anchor)
{
	sf::Sprite redLdb;
	redLdb.setTexture(context.textures->get(Texture::ID::NormalLadyBug));
	redLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::RedLadybug)] = redLdb;

	sf::Sprite redBlackLdb;
	redBlackLdb.setTexture(context.textures->get(Texture::ID::DefensiveLadyBug));
	redBlackLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::RedBlackLadybug)] = redBlackLdb;

	sf::Sprite blackLdb;
	blackLdb.setTexture(context.textures->get(Texture::ID::OffensiveLadyBug));
	blackLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::BlackLadybug)] = blackLdb;

	sf::Sprite aphid;
	aphid.setTexture(context.textures->get(Texture::ID::Aphid));
	aphid.setOrigin(50.0f, 75.0f);
	mInsectSprites[static_cast<int>(Insect::Aphid)] = aphid;

	mBackGround.setTexture(context.textures->get(Texture::ID::BackGround));

	/*
	for (auto flower : mRoseTree.getFlowers())
	{
		//ID<Flower> flower = stuff.first;
		switch (mRoseTree[flower].getType())
		{
			case Flower::Type::RegularFlower:
				mFlowers.push_back(new Flower(flower, 5, sf::seconds(60), Flower::Type::RegularFlower));
				break;
			case Flower::Type::AphidFlower:
				mFlowers.push_back(new Flower(flower, 5, sf::seconds(0), Flower::Type::AphidFlower));
				break;
			case Flower::Type::LadyBugFlower:
				mFlowers.push_back(new Flower(flower, 5, sf::seconds(3), Flower::Type::LadyBugFlower));
				break;
			default:
				break;
		}
	}
	*/
}

GameWorld::~GameWorld()
{

}


void GameWorld::render(sf::RenderTarget& target)
{
	target.draw(mBackGround);
//	mRoseTree.draw(target, sf::RenderStates::Default); // TODO À faire, mais différement
	for (auto ldb : mLadyBugs) {
		ldb->draw(target, mRoseTree, mInsectSprites[static_cast<size_t>(ldb->getType())]);
	}
	for (auto &apd : mAphids) {
		apd->draw(target, mRoseTree, mInsectSprites[static_cast<size_t>(Insect::Aphid)]);
	}
}

Insect* GameWorld::spawnInsect(Insect::Type type, ID<Flower> flower)
{
	if (type == Insect::Aphid)
	{
		mAphids.push_back(new Aphid(AphidBehaviour::Offensive, flower, mRoseTree));
		return *mAphids.end();
	} else {
		mLadyBugs.push_back(new LadyBug(type, flower, mRoseTree));
		mAnchorPool.addAnchor<InsectAnchorListener>(AnchorItem(20.f), *mLadyBugs.back());
		return * --mLadyBugs.end();
	}
}

ID<Flower> GameWorld::spawnNode(sf::Vector2f position, Flower::Type type)
{
	// TODO FIXME
	return mRoseTree.addFlower(position, type);
}


void GameWorld::update(sf::Time dt)
{
  for (auto &ldb : mLadyBugs)
  {
    if (!ldb->getBusy())
        ldb->move(dt.asSeconds(), mRoseTree);
    ldb->setBusyTime(ldb->getBusyTime() + dt);
    if (ldb->getBusyTime() > sf::seconds(3))
    {
        ldb->setBusy(false);
        ldb->setBusyTime(sf::seconds(0));
    }
    for (unsigned int i=0; i<mAphids.size(); ++i)
    {
        Aphid *apd = mAphids[i];
        if (ldb->getBranchID() == apd->getBranchID())
        {
			// TODO Faudrait changer ça…
            if (ldb->getPos(mRoseTree) < apd->getPos(mRoseTree)+0.1
				&& ldb->getPos(mRoseTree) > apd->getPos(mRoseTree)-0.1
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
    apd->move(dt.asSeconds(), mRoseTree);
    if (apd->isObjectiveReached())
    {
        ID<Flower> flower = apd->getPrevFlower();
		if (mRoseTree[flower].loseOnePoint())
			mRoseTree.removeFlower(flower);
		/*
        for (unsigned int j=0; j<mRoseTree.getFlowerNumber(); ++j)
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
		*/
        mAphids.erase(mAphids.begin()+i);
    }
  }
  /* FIXME Il faut y faire quelque chose, pour l’instant on fait rien…
  for (auto flowerID : mRoseTree.getFlowers()) {
	Flower& flower = mRoseTree[flowerID];
    bool isReady = flower.update(dt);
    if (isReady)
    {
        Flower::Type type = flower.getType();
        if (type == Flower::AphidFlower)
        {
            if (flower.getCurrentTime() > sf::seconds(4))
            {
                spawnInsect(Insect::Aphid, Node::ID(*flower));
                flower.setCurrentTime(sf::seconds(0));
            }
        }
        if (type == Texture::ID::LadyBugFlower)
        {
			ID<Flower> flower = *flower;
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
  */
}


