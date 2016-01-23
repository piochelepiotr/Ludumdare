#pragma once
#include "insect/insect.hpp"
#include "rosetree/rosetree.inl"

// Insect

ID<Branch> Insect::getBranch() const
{ return mRoseTree.getBranchID(mPath.getTwoFirstNodes()); }
ID<Flower> Insect::getPrevFlower() const
{ return mPath.getFirstNode(); }
bool Insect::isObjectiveReached() const
{ return mPath.isEmpty(); }

sf::Vector2f Insect::getPosition() const
{ return mRealPosition; }

ID<Flower> Insect::getNextFlower() const
{ return mPath.getTwoFirstNodes().second; }

Branch const& Insect::getRealBranch() const
{ return mRoseTree.getBranch(mPath.getTwoFirstNodes()); }


// Aphid

void Aphid::move(sf::Time dt)
{ Insect::move(dt); }


// LadyBug

LadyBug::LadyBug(RoseTree const& rt, ID<Flower> spawnFlower, LadyBug::Type t) :
	Insect(rt, spawnFlower, 50.f*1.5f), mDutyPath(spawnFlower), mType(t)
{ move(sf::seconds(0.f)); } // Juste pour faire la mise au point du path

void LadyBug::eatAnAphid(Aphid& aphid)
{ mEatingTime = sf::seconds(0.2f); }
bool LadyBug::isEating()
{ return mEatingTime > sf::seconds(0); }
void LadyBug::decreaseEatingTime(sf::Time dt)
{ mEatingTime -= dt; }
