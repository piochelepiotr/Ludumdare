#pragma once
#include "node.hpp"

class Flower : public Node
{
public:
    Flower(Node::ID id);
    bool loseOnePoint();//returns false if the flower dies
    bool isLadyBugFlower();
    bool update(sf::Time dt);//returns true if the flower fades
    void becameNode();
    
private:
    int mLife;
    sf::Time mCurrentTime;
    static const int mStartLifePoints;
    static const sf::Time mLifeDuration;
};