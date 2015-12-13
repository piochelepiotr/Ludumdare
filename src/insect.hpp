#pragma once
#include "behaviour.hpp"
#include <cmath>

class Insect {
public:
  enum type {RedLadybug, RedBlackLadybug, BlackLadybug, Aphid};
  Insect(type mType, float hitbox, int currentBranch, float pos, float speed, float angle);
  void move(float dt, Graph *g);
  void draw(sf::RenderTarget& target, Graph *g, sf::Sprite sprite);
  type getType();
protected:
  Path path;
  type mType;
  sf::CircleShape hitbox;
  int currentBranch;
  float pos;
  float speed;
  float angle;
};

class Aphid : public Insect {
public:
  Aphid(AphidBehaviour::ID b, Node spawn, Graph *g);
private:
  AphidBehaviour behaviour;
};

class LadyBug : public Insect {
public:
  LadyBug(Insect::type type, Node spawn, Graph *g);
private:
  bool busy;
};


