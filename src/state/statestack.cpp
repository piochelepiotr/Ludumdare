#include "statestack.hpp"
#include <cassert>

StateStack::StateStack(StateContext context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{

}

State::Ptr StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if ((*itr)->handleEvent(event))
			break;
	}
	applyPendingChanges();
	return;
}

void StateStack::update(sf::Time dt)
{
	applyPendingChanges();
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
            break;
    }
}

void StateStack::draw()
{
	mContext.window->clear();
    for (auto it = mStack.begin(); it != mStack.end(); ++it)
        (*it)->draw();
    mContext.window->display();
}

void StateStack::applyPendingChanges()
{
    for (PendingChange change: mPendingList)
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;
            case Pop:
                mStack.pop_back();
                break;
            case Clear:
                mStack.clear();
                break;
        }
    }
    mPendingList.clear();
}

void StateStack::pushState(States::ID stateID)
{
    struct PendingChange change;
    change.action = Push;
    change.stateID = stateID;
    mPendingList.push_back(change);
}

void StateStack::popState()
{
    if (isEmpty())
        return;
    struct PendingChange change;
    change.action = Pop;
    change.stateID = States::Title;
    mPendingList.push_back(change);
}

void StateStack::clearStates()
{
    struct PendingChange change;
    change.action = Clear;
    change.stateID = States::Title;
    mPendingList.push_back(change);
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}
