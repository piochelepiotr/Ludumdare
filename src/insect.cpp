#include "insect.hpp"

Aphid::Aphid(Behaviour::id b, Node spawn, Graph *g) : mType(Insect::APHID)
						    , hitbox(10)
						    , behaviour(b, spawn, g)
						    , currentBranch(0)
						    , pos(0.0f)
						    , speed(1.0f)
{
  currentBranch = behaviour.getPath().get(0).sd;
}

void Aphid::move(dt) {
  pos += speed * dt;
  if (pos > 1.0f) {
    
  }
}

