#include "rosetree/flower.hpp"
#include <cassert>

sf::Time getTimeFromType(Flower::Type type);

Flower::Flower(sf::Vector2f position, Type type) :
	mPosition(position), mDerivative(), mType(type), mLife(50), mTimeLeft(getTimeFromType(type))
{
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


void Flower::setTimeLeft(sf::Time t)
{ mTimeLeft = t; }

bool Flower::update(sf::Time dt)
{
	mTimeLeft -= dt;
	return mTimeLeft <= sf::seconds(0);
}
void Flower::becomeNode()
{
	mType = Node;
	mTimeLeft = sf::seconds(1);
}



// Types

Flower::Type Flower::getType() const
{ return mType; }

void Flower::setType(Type t)
{ mType = t; }

Flower::Type Flower::nextType()
{
	int newType = static_cast<int>(mType) + 1;
	if (newType > static_cast<int>(TypeEnumSize))
		newType = 0;
	return mType = Type(newType);
}

sf::Time getTimeFromType(Flower::Type type)
{
	switch (type)
	{
		case Flower::AphidFlower:
			return sf::seconds(0.9f);
		case Flower::LadybugFlower:
			return sf::seconds(2.f);
		default:
			return sf::seconds(1.f);
	}
}

std::ostream& operator<<(std::ostream& os, Flower::Type const& type)
{
	char const* s;
	switch (type)
	{
		case Flower::RegularFlower:
			s = "RegularFlower";
			break;
		case Flower::AphidFlower:
			s = "AphidFlower";
			break;
		case Flower::LadybugFlower:
			s = "LadybugFlower";
			break;
		case Flower::Node:
			s = "Node";
			break;
		case Flower::TypeEnumSize:
			assert(false); // This case should never happen
			break;
	}
	return os << s;
}

std::istream& operator>>(std::istream& is, Flower::Type& type)
{
	// I don't think there is a better way…
	// (Except a more smart if/else system, like dichotomic research,
	// but it would be ugly and hard to maintain)
	std::string s;
	is >> s;
	if (s == "RegularFlower")
		type = Flower::RegularFlower;
	else if (s == "AphidFlower")
		type = Flower::AphidFlower;
	else if (s == "LadybugFlower")
		type = Flower::LadybugFlower;
	else if (s == "Node")
		type = Flower::Node;
	else
		is.setstate(is.failbit);
	return is;
}
