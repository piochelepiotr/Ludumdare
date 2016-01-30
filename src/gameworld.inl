#pragma once
#include "gameworld.hpp"
#include "rosetree/rosetree.inl"

// Flowers

ID<Flower> GameWorld::addFlower(sf::Vector2f position, Flower::Type type)
{ return mRoseTree.addFlower(position, type); }

void GameWorld::removeFlower(ID<Flower> flower)
{ return mRoseTree.removeFlower(flower); }

ID<Flower> GameWorld::spawnFlower(sf::Vector2f position, Flower::Type type)
{ return mRoseTree.addFlower(position, type); }

Flower::Type GameWorld::nextType(ID<Flower> f)
{ return mRoseTree[f].nextType(); }


// Branchs


// Insects


// Get everything

IDstaticmap<Flower> const& GameWorld::getFlowers() const
{ return mRoseTree.getFlowers(); }

IDstaticmap<Branch> const& GameWorld::getBranchs() const
{ return mRoseTree.getBranchs(); }

std::vector<Ladybug*> const& GameWorld::getLadybugs() const
{ return mLadybugs; }

std::vector<Aphid*> const& GameWorld::getAphids() const
{ return mAphids; }


// Capacity

int GameWorld::getRemainingCapacity() const
{ return mRemainingCapacity; }

int GameWorld::getTotalCapacity() const
{ return mTotalCapacity; }

void GameWorld::useCapacity(int usedCapacity)
{ mRemainingCapacity -= usedCapacity; }

void GameWorld::increaseTotalCapacity()
{ ++mTotalCapacity; ++mRemainingCapacity; }


// Input-Output

void GameWorld::load(std::istream& is)
{ mRoseTree.load(is); }

void GameWorld::save(std::ostream& os) const
{ mRoseTree.save(os); }

