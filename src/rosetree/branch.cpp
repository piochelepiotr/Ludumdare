#include "rosetree/branch.hpp"
#include "rosetree/rosetree.hpp"
#include "rosetree/flower.hpp"

Branch::Branch(RoseTree& rt, ID<Flower> f1, ID<Flower> f2, Type t) :
	mFirstFlower(std::min(f1, f2)), mSecondFlower(std::max(f1, f2)),
	mType(t),
	mLadybugNumber(0),
	mSplineShape(createSplineShape(rt[mFirstFlower], rt[mSecondFlower]))
{ }

SplineShape Branch::createSplineShape(Flower& f1, Flower& f2)
{
	sf::Vector2f defaultDerivative = f2.getPosition() - f1.getPosition();
	return SplineShape(3.0f, 30,
			f1.getPosition(), f2.getPosition(),
			f1.initDerivative(defaultDerivative),
			f2.initDerivative(defaultDerivative));
}

// TODO These seven functions: inline them!
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
{
	return f0 == mFirstFlower ? pos : 1.f - pos;
}
sf::Vector2f Branch::eval(float pos, ID<Flower> firstFlower) const
{
	float f = firstFlower == mFirstFlower ? pos : 1.f - pos;
	return mSplineShape.getSpline().evaluatePos(f);
}

sf::Vector2f Branch::evalDerivative(float pos, ID<Flower> firstFlower) const
{
	if (firstFlower == mFirstFlower)
		return mSplineShape.getSpline().evaluateSpeed(pos);
	else
		return - mSplineShape.getSpline().evaluateSpeed(1.f - pos);
}
