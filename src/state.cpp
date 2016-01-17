#include "state.hpp"
#include "statestack.hpp"

State::State(StateStack& mystack, StateContext context)
: mStack(&mystack)
, mContext(context)
{

}

State::~State()
{

}

void State::requestStackPush(States::ID stateID)
{
    mStack->pushState(stateID);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStackClear()
{
    mStack->clearStates();
}

StateContext State::getContext() const
{
    return mContext;
}
