#include "rosetree/flower.hpp"
#include <iostream>
#include <map>

sf::Time getTimeFromType(Flower::Type type)
{
	switch (type)
	{
		case Flower::AphidFlower:
			return sf::seconds(2.f);
		case Flower::LadybugFlower:
			return sf::seconds(5.f);
		default:
			return sf::seconds(1.f);
	}
}

Flower::Flower(sf::Vector2f position, Type type) :
	mPosition(position), mDerivative(), mType(type), mLife(10), mTimeLeft(getTimeFromType(type))
{
}


Flower::Type Flower::typeFromString(std::string str)
{
	// FIXME Very bad idea: What if we add new types?
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
	std::cerr << "Hi, I have been attacked and my life is now : " << mLife << std::endl;
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


void Flower::setTimeLeft(sf::Time t)
{ mTimeLeft = t; }

bool Flower::update(sf::Time dt)
{
	mTimeLeft -= dt;
	return mTimeLeft <= sf::seconds(0);
}
void Flower::becomeNode()
{
	mType = RegularFlower;
	mTimeLeft = sf::seconds(1);
}
