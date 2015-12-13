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
  for (auto &ldb : mLadyBugs) {
    ldb.move(dt.asSeconds(), mGraph);
  }
  for (auto &apd : mAphids) {
    apd.move(dt.asSeconds(), mGraph);
  }
  for (auto &flower : mFlowers) {
    bool isReady = flower.update(dt);
    if (isReady)
    {
        Node::Type type = flower.getType();
        if (type == Texture::ID::AphidFlower)
        {
            spawnInsect(Insect::Aphid, flower);
            flower.becameNode();
        }
        if (type == Texture::ID::LadyBugFlower)
        {
            spawnInsect(Insect::BlackLadybug, flower);
            flower.becameNode();
        }
    }
  }
}


