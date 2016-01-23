#include "rosetree/branch.hpp"
#include "rosetree/rosetree.hpp"
#include "rosetree/flower.hpp"

Branch::Branch(ID<Flower> f1, ID<Flower> f2, Type t, RoseTree& rt) :
	Branch(HelpCreator(f1, f2, t, rt))
{}

Branch::HelpCreator::HelpCreator(ID<Flower> _f1, ID<Flower> _f2, Type _t, RoseTree& rt) :
	f1ID(_f1), f2ID(_f2), type(_t), f1(&rt[f1ID]), f2(&rt[f2ID])
{
	// On s’arrange pour placer la fleur la plus basse en tant que f1
	if (f2->getPosition().y < f1->getPosition().y)
	{
		// On échange
		auto tempID = f1ID; f1ID = f2ID; f2ID = tempID;
		auto temp = f1; f1 = f2; f2 = temp;
	}
}

SplineShape Branch::createSplineShape(Flower& f1, Flower& f2)
{
	sf::Vector2f defaultDerivative = 1.3f*(f2.getPosition() - f1.getPosition());
	return SplineShape(3.0f, 30,
			f1.getPosition(), f2.getPosition(),
			f1.initDerivative(defaultDerivative),
			f2.initDerivative(defaultDerivative));
}


Branch::Branch(HelpCreator hc) :
	mFirstFlower(hc.f1ID), mSecondFlower(hc.f2ID),
	mType(hc.type),
	mSplineShape(createSplineShape(*hc.f1, *hc.f2)),
	mLadybugNumber(0)
{ }


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

void Branch::draw(sf::RenderTarget& target) const
{
	target.draw(mSplineShape);
}
