#include "insect.hpp"

void Insect::draw(sf::RenderTarget& target, Graph *g, sf::Sprite sprite) {
  Branch b = g->getBranch(path.getBranchID(currentBranch));
  sf::Vector2f posVect = b.getSpline().evaluatePos(pos);
  sf::Vecrot2f speedVect = b.getSpline().evaluateSpeed(pos);
  angle = arctan(speedVect.y / speedVect.x); // BE FUCKING CAREFUL THERE, BUDDY
  hitbox.setPosition(posVect);
  target.draw(hitbox);
}

void Insect::move(dt) {
  pos += speed * dt;
  if (pos > 1.0f) {
    pos = 0.0f;
    currentBranch += 1;
    if (currentBranch == path.length())
      currentBranch = 0;
  }
}

Aphid::Aphid(Behaviour::id b, Node spawn, Graph *g) : mType(Insect::APHID)
						    , hitbox(10)
						    , behaviour(b, spawn, g)
						    , currentBranch(0)
						    , pos(0.0f)
						    , speed(1.0f)
						    , angle(0.0f)
						    , path()
{
  path = behaviour.getPath();
}


LadyBug::LadyBug() : mType(Insect::LADYBUG)
		   , hitbox(12)
		   , currentBranch(0)
		   , pos(0.0f)
		   , speed(1.5f)
		   , angle(0.0f)
		   , path()
{
  
}
