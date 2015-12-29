#pragma once
#include "behaviour.hpp"
//#include <cmath>
#include "rosetree/rosetree.hpp"
#include "rosetree/path.hpp"
#include <SFML/Graphics.hpp>

class Insect {
public:

  enum Type {RedLadybug, RedBlackLadybug, BlackLadybug, Aphid};

  Insect(Type mType, ID<Flower> node, float fhitbox, float speed, float angle);
  void move(float dt, RoseTree const& rt); // C’est très casse-gueule, parce qu’il y a aussi une méthode move pour les coccinelles…
  void draw(sf::RenderTarget& target, RoseTree const& rt, sf::Sprite sprite);

  Type getType();
  Branch const& getBranch() const { return roseTree.getBranch(path.getTwoFirstNodes()); }
  ID<Branch> getBranchID() const { return roseTree.getBranchID(path.getTwoFirstNodes()); }
  float getPos(RoseTree const& rt) const;
  bool isObjectiveReached() const { return path.isEmpty(); }
  ID<Flower> getPrevFlower() const { return path.getFirstNode(); }
  ID<Flower> getNextFlower() const { return path.getTwoFirstNodes().second; }
//  ID<Flower> getObjective() { return objective; }
  sf::Vector2f getPosition() const;

  void setDisplayCircle(bool display);

protected:
  Type mType;
  Path<Flower> path;
  RoseTree const roseTree;
  sf::CircleShape hitbox;
  float pos;
  float speed;
  float angle;
//  ID<Flower> objective;
  bool mDisplay=false;
};

class Aphid : public Insect {
public:
  Aphid(AphidBehaviour::Type b, ID<Flower> spawn, RoseTree const& rt);
private:
  AphidBehaviour behaviour;
};

class LadyBug : public Insect {
public:
  LadyBug(Insect::Type type, ID<Flower> spawn, RoseTree const& rt);
  void redefinePath(Path<Flower> newPath, RoseTree const& rt);
  void move(float dt, RoseTree const& rt);
  void setBusy(bool bo){busy = bo;};
  bool getBusy(){return busy;};
  void setBusyTime(sf::Time dt){busyTime = dt;};
  sf::Time getBusyTime(){return busyTime;};

private:
  Path<Flower> dutyPath;
  bool busy;
  sf::Time busyTime = sf::seconds(0);
};


