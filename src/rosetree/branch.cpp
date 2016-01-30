#include "rosetree/branch.hpp"
#include "rosetree/rosetree.hpp"
#include "rosetree/flower.hpp"
#include "rosetree/branch.inl"

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


sf::Vector2f Branch::evalDerivative(float pos, ID<Flower> firstFlower) const
{
	auto spline = mSplineShape.getSpline();
	float realPos = getPos(pos, firstFlower);
	sf::Vector2f derivative = spline.evaluateSpeed(realPos);
	if (firstFlower == mFirstFlower)
		return derivative;
	else
		return - derivative;
}
