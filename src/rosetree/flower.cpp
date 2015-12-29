#include "rosetree/flower.hpp"
#include <map>

Flower::Flower(sf::Vector2f position, Type type) :
	mPosition(position), mDerivative(), mType(type), mLife(50)
{}


Flower::Type Flower::typeFromString(std::string str)
{
	// FIXME Very bad ID: What if we add new types?
	static std::map<std::string, Type> typeMap = {
		std::make_pair("RegularFlower", RegularFlower),
		std::make_pair("AphidFlower", AphidFlower),
		std::make_pair("LadybugFlower", LadybugFlower),
		std::make_pair("None", None)
	};
	return typeMap[str];
}

Flower::Type Flower::getType() const
{ return mType; }

void Flower::setType(Type t)
{ mType = t; }

// FIXME Not very cool…
Flower::Type Flower::changeType()
{
	int newType = static_cast<int>(mType) + 1;
	if (newType > static_cast<int>(Type::None))
		newType = 0;
	return mType = Type(newType);
}

bool Flower::loseOnePoint()
{
	mLife--;
	return mLife > 0;
}

sf::Vector2f Flower::getPosition() const
{ return mPosition; }

sf::Vector2f Flower::getDerivative() const
{ return mDerivative; }

sf::Vector2f Flower::initDerivative(sf::Vector2f deriv)
{
	if (mDerivative == sf::Vector2f())
		mDerivative = deriv;
	return mDerivative;
}

bool Flower::update(sf::Time dt)
{
	mLeftTime -= dt;
	return mLeftTime <= sf::seconds(0);
}
