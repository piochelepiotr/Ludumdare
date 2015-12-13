#pragma once
#include "behaviour.hpp"
#include <cmath>

class Insect {
public:
  enum type {LADYBUG, APHID};
  Insect(type mType, float hitbox, int currentBranch, float pos, float speed, float angle);
  void move(float dt, Graph*);
  void draw(sf::RenderTarget& target, Graph *g, sf::Sprite sprite);
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
  Aphid(Behaviour::ID b, Node spawn, Graph *g);
private:
  Behaviour behaviour;
};

class LadyBug : public Insect {
public:
  LadyBug(Node spawn, Graph *g);
private:
  bool busy;
};


