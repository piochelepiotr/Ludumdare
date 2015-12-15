#pragma once
#include "behaviour.hpp"
#include <cmath>

class Graph;

class Insect {
public:

  enum type {RedLadybug, RedBlackLadybug, BlackLadybug, Aphid};

  Insect(type mType, Node::ID node, float fhitbox, float speed, float angle);
  void move(float dt, Graph const&g); // C’est très casse-gueule, parce qu’il y a aussi une méthode move pour les coccinelles…
  void draw(sf::RenderTarget& target, Graph const&g, sf::Sprite sprite);

  type getType();
  Branch::ID getBranch() const { return path.frontBranch(); }
  float getPos(Graph const&) const;
  bool isObjectiveReached() const { return path.isEmpty(); }
  Node::ID getPrevNode() const { return path.getPrevNode(); }
//  Node::ID getObjective() { return objective; }
  sf::Vector2f getPosition() const;

  void setDisplayCircle(bool display);

protected:
  type mType;
  Path path;
  sf::CircleShape hitbox;
  float pos;
  float speed;
  float angle;
//  Node::ID objective;
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
  void redefinePath(Path newPath, Graph const& g);
  void move(float dt, Graph const& g);
  void setBusy(bool bo){busy = bo;};
  bool getBusy(){return busy;};
  void setBusyTime(sf::Time dt){busyTime = dt;};
  sf::Time getBusyTime(){return busyTime;};

private:
  Path dutyPath;
  bool busy;
  sf::Time busyTime = sf::seconds(0);
};


