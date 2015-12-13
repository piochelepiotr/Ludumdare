#include "flower.hpp"

int Flower::mStartLifePoints = 5;
sf::Time Flower::mLifeDuration = sf::Time(60000000);//time in microseconds
int Flower::mRaduis = 50;
sf::Time mTimeBetweenGeration = sf::Time(20000000);

Flower::Flower(Node::ID id,sf::Time startTime): Node(id)
{
    mLife = mStartLifePoints;
    mStartTime = startTime;
    mTimeLastGeneration = startTime;
}

bool Flower::loseOnePoint()
{
    mLife--;
    return mLife;
}

bool Flower::isFaded(sf::Time time)
{
    return time - mStartTime >= mLifeDuration;
}

bool Flower::generateLadyBug(sf::Time time)
{
    if(time-mTimeLastGeneration > mTimeBetweenGeration)
    {
	mTimeLastGeneration = time;
	return true;
    }
    else
    {
	return false;
    }
}



