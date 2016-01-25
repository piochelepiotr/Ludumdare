#include "editlevelstate.hpp"
#include "gameworld.inl"
#include <fstream>


EditLevelState::EditLevelState(StateStack& mystack, StateContext context) :
	GameState(mystack, context, GameWorld::EditMode)
{
}

EditLevelState::~EditLevelState()
{
	save("niveau1.txt");
}

void EditLevelState::save(std::string name)
{
	std::ofstream file(name);
	mGameWorld.save(file);
	file.close();
}
