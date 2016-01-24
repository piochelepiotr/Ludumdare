#pragma once
#include "gameworld.hpp"
#include "rosetree/rosetree.inl"

// RoseTree

ID<Flower> GameWorld::addFlower(sf::Vector2f position, Flower::Type type)
{ return mRoseTree.addFlower(position, type); }
void GameWorld::removeFlower(ID<Flower> flower)
{ return mRoseTree.removeFlower(flower); }
IDstaticmap<Flower>& GameWorld::getFlowers()
{ return mRoseTree.getFlowers(); }
ID<Flower> GameWorld::spawnFlower(sf::Vector2f position, Flower::Type type)
{ return mRoseTree.addFlower(position, type); }
Flower::Type GameWorld::nextType(ID<Flower> f)
{ return mRoseTree[f].nextType(); }

// Capacity

void GameWorld::useCapacity(int usedCapacity)
{ mLeftCapacity -= usedCapacity; }
int GameWorld::getLeftCapacity()
{ return mLeftCapacity; }
int GameWorld::getTotalCapacity()
{ return mTotalCapacity; }
void GameWorld::increaseTotalCapacity()
{ ++mTotalCapacity; ++mLeftCapacity; }


// Input-Output

void GameWorld::load(std::istream& is)
{ mRoseTree.load(is); }
void GameWorld::save(std::ostream& os) const
{ mRoseTree.save(os); }

