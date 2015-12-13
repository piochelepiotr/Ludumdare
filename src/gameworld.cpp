#include "gameworld.hpp"

GameWorld::GameWorld() {
  
}

GameWorld::~GameWorld()
{

}


void GameWorld::render(sf::RenderTarget& target)
{
  target.draw(mBackGround);
  for (auto &ldb : mLadyBugs) {
    ldb.draw(target, &mGraph, sf::Sprite());
  }
  for (auto &apd : mAphids) {
    apd.draw(target, &mGraph, sf::Sprite());
  }
}

void GameWorld::spawnInsect(Insect::type type, Node node)
{
  if (type == Insect::LADYBUG) {
    mLadyBugs.push_back(LadyBug(node, &mGraph));
  } else {
    mAphids.push_back(Aphid(Behaviour::Dumb, node, &mGraph));
  }
}

void GameWorld::spawnNode(NodeType type, sf::Vector2f position)
{
    
}


void GameWorld::update(sf::Time time)
{

}


