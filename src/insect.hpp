#pragma once
#include "behaviour.hpp"

class Insect {
public:
  enum type {LADYBUG, APHID};
  Insect() = default;
  void move(float dt);
  void draw(sf::RenderTarget& target);
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
  Aphid(Behaviour::id b, Node spawn, Graph *g);
private:
  Behaviour behaviour;
};

class LadyBug : public Insect {
public:
  LadyBug(Node spawn, Graph *g);
private:
  bool busy;
};


