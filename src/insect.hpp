#pragma once
#include "behaviour.hpp"

class Insect {
enum type {LADYBUG, APHID};
public:
  Insect() = default;
protected:
  type mType;
  sf::CircleShape hitbox;
  Branch currentBranch;
  float pos;
};

class Aphid : public Insect {
public:
  Aphid(Behaviour::id b, Node spawn, Graph *g);
private:
  Behaviour behaviour;
};

class LadyBug : public Insect {
public:
  LadyBug();
private:
  bool busy;
};


