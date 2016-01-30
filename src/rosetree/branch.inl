#include "rosetree/branch.hpp"

Branch::Branch(ID<Flower> f1, ID<Flower> f2, Type t, RoseTree& rt) :
	Branch(HelpCreator(f1, f2, t, rt))
{}

ID<Flower> Branch::getFirstFlower() const
{ return mFirstFlower; }
ID<Flower> Branch::getSecondFlower() const
{ return mSecondFlower; }

float Branch::getLength() const
{ return mSplineShape.getLength(); }

unsigned int Branch::getLadybugNumber() const
{ return mLadybugNumber; }

Branch::Type Branch::getType() const
{ return mType; }

void Branch::setLadybugNumber(unsigned int nb)
{ mLadybugNumber = nb; }

void Branch::setType(Type t)
{ mType = t; }


float Branch::getPos(float pos, ID<Flower> f0) const
{ return f0 == mFirstFlower ? pos : 1.f - pos; }

sf::Vector2f Branch::eval(float pos, ID<Flower> firstFlower) const
{
	float realPos = getPos(pos, firstFlower);
	return mSplineShape.getSpline().evaluatePos(realPos);
}

void Branch::draw(sf::RenderTarget& target) const
{
	target.draw(mSplineShape);
}
