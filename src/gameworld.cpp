#include "gameworld.hpp"
#include <iostream>

//GameWorld::GameWorld()
//{

//}

//GameWord

	GameWorld::GameWorld(sf::Sprite redLdb, sf::Sprite redBlackLdb, sf::Sprite blackLdb, sf::Sprite aphid, sf::Sprite backGround, Graph& g)
	: mGraph(&g)
	, mLadyBugs()
	, mAphids()
	, mFlowers()
	, mBackGround(backGround)
	  , mInsectSprites()
{
	redLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::RedLadybug)] = redLdb;
	redBlackLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::RedBlackLadybug)] = redBlackLdb;
	blackLdb.setOrigin(50.0f, 70.0f);
	mInsectSprites[static_cast<int>(Insect::BlackLadybug)] = blackLdb;
	aphid.setOrigin(50.0f, 75.0f);
	mInsectSprites[static_cast<int>(Insect::Aphid)] = aphid;

	for (auto& stuff : *mGraph)
	{
		Node::ID node = stuff.first;
		if (g[node].m_t == Texture::ID::AphidFlower)
		{
			mFlowers.push_back(Flower(node, 5, sf::seconds(1), Texture::ID::AphidFlower));
		}
		if (g[node].m_t == Texture::ID::Flower)
		{
			mFlowers.push_back(Flower(node, 5, sf::seconds(60), Texture::ID::Flower));
		}
		if (g[node].m_t == Texture::ID::LadyBugFlower)
		{
			mFlowers.push_back(Flower(node, 5, sf::seconds(3), Texture::ID::LadyBugFlower));
		}
	}
}

GameWorld::~GameWorld()
{

}


void GameWorld::render(sf::RenderTarget& target)
{
	target.draw(mBackGround);
	mGraph->draw(target, sf::RenderStates::Default);
	for (auto &ldb : mLadyBugs) {
		ldb.draw(target, mGraph, mInsectSprites[static_cast<size_t>(ldb.getType())]);
	}
	for (auto &apd : mAphids) {
		apd.draw(target, mGraph, mInsectSprites[static_cast<size_t>(Insect::Aphid)]);
	}
}

void GameWorld::spawnInsect(Insect::type type, Node node)
{
	if (type == Insect::Aphid) {
		mAphids.push_back(Aphid(AphidBehaviour::Offensive, node, mGraph));
	} else {
		mLadyBugs.push_back(LadyBug(type, node, mGraph));
	}
}

void GameWorld::spawnNode(NodeType type, sf::Vector2f position)
{

}


void GameWorld::update(sf::Time dt)
{
  for (auto &ldb : mLadyBugs)
    {
    if (!ldb.getBusy())
        ldb.move(dt.asSeconds(), mGraph);
    ldb.setBusyTime(ldb.getBusyTime() + dt);
    if (ldb.getBusyTime() > sf::seconds(3))
    {
        ldb.setBusy(false);
        ldb.setBusyTime(sf::seconds(0));
    }
    for (unsigned int i=0; i<mAphids.size(); ++i)
    {
        Aphid &apd = mAphids[i];
        if (ldb.getBranch() == apd.getBranch())
        {
            if (ldb.getPos(mGraph) < apd.getPos(mGraph)+0.1 && ldb.getPos(mGraph) > apd.getPos(mGraph)-0.1 && !ldb.getBusy())
            {
                ldb.setBusy(true);
                mAphids.erase(mAphids.begin()+i);
            }
        }
    }
  }
  for (unsigned int i=0; i<mAphids.size(); ++i)
  {
    Aphid &apd = mAphids[i];
    apd.move(dt.asSeconds(), mGraph);
    if (apd.getReachedObjective())
    {
        Node::ID node = apd.getObjective();
        for (unsigned int j=0; j<mFlowers.size(); ++j)
        {
            Flower &flower = mFlowers[j];
            if (flower == node)
            {
                if (flower.loseOnePoint())
                {
                    mFlowers.erase(mFlowers.begin()+i);
                }
            }
        }
        mAphids.erase(mAphids.begin()+i);
    }
  }
  for (auto &flower : mFlowers) {
    bool isReady = flower.update(dt);
    if (isReady)
    {
        Node::Type type = flower.getType();
        if (type == Texture::ID::AphidFlower)
        {
            if (flower.getCurrentTime() > sf::seconds(2))
            {
                spawnInsect(Insect::Aphid, flower);
                flower.setCurrentTime(sf::seconds(0));
            }
        }
        if (type == Texture::ID::LadyBugFlower)
        {
            spawnInsect(Insect::BlackLadybug, flower);
            flower.becameNode();
        }
    }
  }
}


