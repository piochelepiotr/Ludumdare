#pragma once
#include "rosetree/branch.hpp"

Branch::Branch(ID<Flower> f1, ID<Flower> f2, Type t, RoseTree& rt) :
	Branch(HelpCreator(f1, f2, t, rt))
{}

Branch::Branch(HelpCreator hc) :
	mFirstFlower(hc.f1ID), mSecondFlower(hc.f2ID),
	mType(hc.type),
	mSpline(createSpline(*hc.f1, *hc.f2)),
	mLadybugNumber(0)
{ }


ID<Flower> Branch::getFirstFlower() const
{ return mFirstFlower; }
ID<Flower> Branch::getSecondFlower() const
{ return mSecondFlower; }

Branch::Type Branch::getType() const
{ return mType; }

float Branch::getLength() const
{ return mSpline.getLength(); }

unsigned int Branch::getLadybugNumber() const
{ return mLadybugNumber; }

Spline const& Branch::getSpline() const
{ return mSpline; }


void Branch::setLadybugNumber(unsigned int nb)
{ mLadybugNumber = nb; }

void Branch::setType(Type t)
{ mType = t; }


float Branch::getPos(float pos, ID<Flower> f0) const
{ return f0 == mFirstFlower ? pos : 1.f - pos; }

sf::Vector2f Branch::eval(float pos, ID<Flower> firstFlower) const
{
	float realPos = getPos(pos, firstFlower);
	return mSpline.evaluatePos(realPos);
}
