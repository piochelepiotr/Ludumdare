#include "insect.hpp"
#include "graph/graph.hpp"

void Insect::draw(sf::RenderTarget& target, Graph *g, sf::Sprite sprite) {
  Branch *b = g->getBranch(path.getBranchID(currentBranch));
  sf::Vector2f posVect = b->getSpline().evaluatePos(pos);
  sf::Vector2f speedVect = b->getSpline().evaluateSpeed(pos);
  angle = atan2(speedVect.y, speedVect.x);

  sprite.setRotation(angle * 180.0f / 3.14159265f);
  sprite.setPosition(posVect);
  hitbox.setPosition(posVect);
  target.draw(hitbox);
  target.draw(sprite);
}

void Insect::move(float dt, Graph* g) {
  pos += speed * dt;
  if (pos > 1.0f) {
    pos = 0.0f;
    currentBranch += 1;
    if (currentBranch == path.length(*g))
      currentBranch = 0;
  }
}

Insect::type Insect::getType() {
  return mType;
}

Insect::Insect(type mType, float hitbox
	       ,int currentBranch
	       , float pos, float speed, float angle) : mType(mType)
						      , hitbox(hitbox)
						      , currentBranch(currentBranch)
						      , pos(pos)
						      , speed(speed)
						      , angle(angle)
{

}

Aphid::Aphid(Behaviour::ID b, Node spawn, Graph *g) : Insect(Insect::Aphid, 10, 0, 0.0f, 1.0f, 0.0f)
						    , behaviour(b, spawn, *g)
{
  path = behaviour.getPath();
}


LadyBug::LadyBug(Insect::type type, Node spawn, Graph *g) : Insect(type, 12, 0, 0.0f, 1.5f, 0.0f)
{

}
