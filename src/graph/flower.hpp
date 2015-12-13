#pragma once
#include "node.hpp"

class Flower : public Node
{
public:
    Flower(Node::ID id,sf::Time startTime);
    bool loseOnePoint();//returns false if the flower dies
    bool isFaded(sf::Time time);
    bool generateLadyBug(sf::Time time);
private:
    int mLife;
    sf::Time mStartTime;
    sf::Time mTimeLastGeneration;//last time when a lady bug was generated
    static const int mStartLifePoints;
    static const sf::Time mLifeDuration;
    static const sf::Time mTimeBetweenGeration;
    static const int mRaduis;
};