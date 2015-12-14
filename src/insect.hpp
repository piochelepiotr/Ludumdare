#pragma once
#include "behaviour.hpp"
#include <cmath>

class Insect {
public:
  enum type {RedLadybug, RedBlackLadybug, BlackLadybug, Aphid};
  Insect(type mType, float hitbox, int currentBranch, float pos, float speed, float angle, Node::ID obj, bool bo);
  void move(float dt, Graph *g);
  void draw(sf::RenderTarget& target, Graph *g, sf::Sprite sprite);
  type getType();
  Branch::ID getBranch(){return path.getBranchID(currentBranch);};
  float getPos(Graph*);
  bool getReachedObjective(){return reachedObjective;};
  Node::ID getObjective(){return objective;};
protected:
  Path path;
  type mType;
  sf::CircleShape hitbox;
  int currentBranch;
  float pos;
  float speed;
  float angle;
  Node::ID objective;
  bool reachedObjective;
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
  void RedefinePath(Path newPath, Graph &g);
  void move(float dt, Graph* g);
  void setBusy(bool bo){busy = bo;};
  bool getBusy(){return busy;};
  void setBusyTime(sf::Time dt){busyTime = dt;};
  sf::Time getBusyTime(){return busyTime;};
private:
  Path futurePath;
  bool busy;
  sf::Time busyTime = sf::seconds(0);
};


