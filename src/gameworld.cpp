#include "gameworld.hpp"

//shouldnt exist
GameWorld::GameWorld() {

}

GameWorld::GameWorld(sf::Sprite redLdb, sf::Sprite redBlackLdb, sf::Sprite blackLdb, sf::Sprite aphid) {
  //looks ugly, but has to be done at some point?
  redLdb.setOrigin(50.0f, 70.0f);
  mInsectSprites[static_cast<int>(Insect::RedLadybug)] = redLdb;
  redBlackLdb.setOrigin(50.0f, 70.0f);  
  mInsectSprites[static_cast<int>(Insect::RedBlackLadybug)] = redBlackLdb;
  blackLdb.setOrigin(50.0f, 70.0f);  
  mInsectSprites[static_cast<int>(Insect::BlackLadybug)] = blackLdb;
  aphid.setOrigin(50.0f, 75.0f);  
  mInsectSprites[static_cast<int>(Insect::Aphid)] = aphid;
}

GameWorld::~GameWorld()
{

}


void GameWorld::render(sf::RenderTarget& target)
{
  target.draw(mBackGround);
  for (auto &ldb : mLadyBugs) {
    ldb.draw(target, &mGraph, mInsectSprites[static_cast<int>(ldb.getType())]);
  }
  for (auto &apd : mAphids) {
    apd.draw(target, &mGraph, mInsectSprites[static_cast<int>(Insect::Aphid)]);
  }
}

void GameWorld::spawnInsect(Insect::type type, Node node)
{
  if (type == Insect::Aphid) {
    mAphids.push_back(Aphid(AphidBehaviour::Dumb, node, &mGraph));
  } else {
    mLadyBugs.push_back(LadyBug(type, node, &mGraph));
  }
}

void GameWorld::spawnNode(NodeType type, sf::Vector2f position)
{
    
}


void GameWorld::update(sf::Time dt)
{
  for (auto &ldb : mLadyBugs) {
    ldb.move(dt.asSeconds(), &mGraph);
  }
  for (auto &apd : mAphids) {
    apd.move(dt.asSeconds(), &mGraph);
  }
}


