#pragma once

#include "statecontext.hpp"
#include <memory>

class StateStack;

namespace States {
	enum ID { Title, Menu, Pause, Game, Speech, Editor };
}

class State
{
	public:
	typedef std::unique_ptr<State> Ptr;

	public:
	State(StateStack& mystack, StateContext context);
	virtual ~State();
	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0; // TODO Expliquer à quoi servent ces bool…
	virtual bool handleEvent(const sf::Event& event) = 0;

	protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStackClear();
	StateContext getContext() const;
	protected:
	StateStack* mStack;
	StateContext mContext;
};
