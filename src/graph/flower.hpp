#pragma once
#include "node.hpp"

class Flower : public Node
{
public:
    Flower(Node::ID, int, sf::Time, Texture::ID);
    bool loseOnePoint();//returns false if the flower dies
    bool isLadyBugFlower();
    bool update(sf::Time);//returns true if the flower fades
    void becameNode();
    sf::Time getCurrentTime()
    {
        return mCurrentTime;
    }
    void setCurrentTime(sf::Time dt){mCurrentTime = dt;};
private:
    int mLife;
    sf::Time mCurrentTime;
    int mStartLifePoints;
    sf::Time mLifeDuration;
};
