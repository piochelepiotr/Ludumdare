#pragma once

#include "gamestate.hpp"

class EditLevelState : public GameState
{
	public:
	EditLevelState(StateStack& mystack, StateContext context);
	virtual ~EditLevelState();

	void save(std::string name);
};
