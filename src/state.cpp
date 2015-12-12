#include "state.hpp"
#include "statestack.hpp"

State::State(StateStack& mystack, Context context)
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

void State::requestStateClear()
{
    mStack->clearStates();
}

State::Context State::getContext() const
{
    return mContext;
}
