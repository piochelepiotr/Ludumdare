#pragma once
#include "insect/insect.hpp"
#include "rosetree/rosetree.inl"
#include "rosetree/rosetree.hpp"

// Insect

ID<Branch> Insect::getBranch() const
{ return mRoseTree.getBranchID(mPath.getTwoFirstNodes()); }
ID<Flower> Insect::getPrevFlower() const
{ return mPath.getFirstNode(); }
bool Insect::isObjectiveReached() const
{ return mPath.isEmpty(); }

sf::Vector2f Insect::getPosition() const
{ return mRealPosition; }
float Insect::getAngle() const
{ return mAngle; }

ID<Flower> Insect::getNextFlower() const
{ return mPath.getTwoFirstNodes().second; }

Branch const& Insect::getRealBranch() const
{ return mRoseTree.getBranch(mPath.getTwoFirstNodes()); }


// Aphid

void Aphid::move(sf::Time dt)
{ Insect::move(dt); }


// Ladybug

Ladybug::Ladybug(RoseTree const& rt, ID<Flower> spawnFlower, Ladybug::Type t) :
	Insect(rt, spawnFlower, 50.f*1.5f), mDutyPath(spawnFlower), mType(t)
{ move(sf::seconds(0.f)); } // Juste pour faire la mise au point du path

void Ladybug::eatAnAphid(Aphid& aphid)
{ mEatingTime = sf::seconds(0.2f); }
bool Ladybug::isEating()
{ return mEatingTime > sf::seconds(0); }
void Ladybug::decreaseEatingTime(sf::Time dt)
{ mEatingTime -= dt; }
