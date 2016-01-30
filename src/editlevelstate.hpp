#pragma once

#include "gamestate.hpp"

// TODO Il faudrait que EditLevelState et GameState héritent tous deux d’un autre state plutôt que EditLevelState hérite de GameState, c’est un peu tordu…
class EditLevelState : public GameState
{
	public:
	EditLevelState(StateStack& mystack, StateContext context);
	virtual ~EditLevelState();

	void save(std::string name);
};
