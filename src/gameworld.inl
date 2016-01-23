#pragma once
#include "gameworld.hpp"
#include "rosetree/rosetree.inl"


ID<Flower> GameWorld::addFlower(sf::Vector2f position, Flower::Type type)
{ return mRoseTree.addFlower(position, type); }
ID<Branch> GameWorld::addBranch(ID<Flower> f1, ID<Flower> f2)
{ return mRoseTree.addBranch(f1, f2); }
IDstaticmap<Flower>& GameWorld::getFlowers()
{ return mRoseTree.getFlowers(); }
ID<Flower> GameWorld::spawnFlower(sf::Vector2f position, Flower::Type type)
{ return mRoseTree.addFlower(position, type); }

// Capacity

void GameWorld::useCapacity(int usedCapacity)
{ mLeftCapacity -= usedCapacity; }
int GameWorld::getLeftCapacity()
{ return mLeftCapacity; }
int GameWorld::getTotalCapacity()
{ return mTotalCapacity; }
void GameWorld::increaseTotalCapacity()
{ ++mTotalCapacity; ++mLeftCapacity; }



