#include "flower.hpp"

Flower::Flower(Node::ID id, int life, sf::Time lifeDuration, Texture::ID type): Node(id)
{
    mStartLifePoints = life;
    mLife = mStartLifePoints;
    mLifeDuration = lifeDuration;
    mCurrentTime = sf::Time();
    m_t = type;
}

bool Flower::loseOnePoint()
{
    mLife--;
    return (mLife<0);
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





