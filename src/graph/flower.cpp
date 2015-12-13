#include "flower.hpp"

int Flower::mStartLifePoints = 5;
sf::Time Flower::mLifeDuration = sf::Time(60000000);//time in microseconds

Flower::Flower(Node::ID id): Node(id)
{
    mLife = mStartLifePoints;
    mCurrentTime = sf::Time();
}

bool Flower::loseOnePoint()
{
    mLife--;
    return mLife;
}

bool Flower::isLadyBugFlower()
{
    return getType() == Texture::ID::LadyBugFlower;
}

void Flower::becameNode()
{
    m_t = Texture::ID::RegularNode;
}

bool Flower::update(sf::Time dt)
{
    mCurrentTime += dt;
    return mCurrentTime >= mLifeDuration;
}





