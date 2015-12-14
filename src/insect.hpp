#pragma once
#include "behaviour.hpp"
#include <cmath>

class Graph;

class Insect {
public:

  enum type {RedLadybug, RedBlackLadybug, BlackLadybug, Aphid};

  Insect(type mType, float hitbox, int currentBranch, float pos, float speed, float angle, Node::ID obj, bool bo);
  void move(float dt, Graph const&g);
  void draw(sf::RenderTarget& target, Graph const&g, sf::Sprite sprite);

  type getType();
  Branch::ID getBranch(){return path.getBranchID(currentBranch);};
  float getPos(Graph const&);
  bool getReachedObjective(){return reachedObjective;};
  Node::ID getObjective(){return objective;};
  sf::Vector2f getPosition() const;

  void setDisplayCircle(bool display);

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
  bool mDisplay=false;
};

class Aphid : public Insect {
public:
  Aphid(AphidBehaviour::ID b, Node::ID spawn, Graph const& g);
private:
  AphidBehaviour behaviour;
};

class LadyBug : public Insect {
public:
  LadyBug(Insect::type type, Node::ID spawn, Graph const& g);
  void RedefinePath(Path newPath, Graph const& g);
  void move(float dt, Graph const& g);
  void setBusy(bool bo){busy = bo;};
  bool getBusy(){return busy;};
  void setBusyTime(sf::Time dt){busyTime = dt;};
  sf::Time getBusyTime(){return busyTime;};

private:
  Path futurePath;
  bool busy;
  sf::Time busyTime = sf::seconds(0);
};


