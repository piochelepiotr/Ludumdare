#include "insect.hpp"

void Insect::draw(sf::RenderTarget& target, Graph *g, sf::Sprite sprite) {
  Branch *b = g->getBranch(path.getBranchID(currentBranch));
  sf::Vector2f posVect = b->getSpline().evaluatePos(pos);
  sf::Vector2f speedVect = b->getSpline().evaluateSpeed(pos);
  angle = atan2(speedVect.x, speedVect.y);
  hitbox.setPosition(posVect);
  target.draw(hitbox);
}

void Insect::move(float dt, Graph* g) {
  pos += speed * dt;
  if (pos > 1.0f) {
    pos = 0.0f;
    currentBranch += 1;
    if (currentBranch == path.length(g))
      currentBranch = 0;
  }
}

Insect::Insect(type mType, float hitbox
	       ,int currentBranch, float pos, float speed, float angle) : mType(mType)
									, hitbox(hitbox)
									, currentBranch(currentBranch)
									, pos(pos)
									, speed(speed)
									, angle(angle)
{

}


Aphid::Aphid(Behaviour::ID b, Node spawn, Graph *g) : Insect(Insect::APHID, 10, 0, 0.0f, 1.0f, 0.0f)
						    , behaviour(b, spawn, g)
{
  path = behaviour.getPath();
}


LadyBug::LadyBug(Node spawn, Graph *g) : Insect(Insect::LADYBUG, 12, 0, 0.0f, 1.5f, 0.0f)
{

}
