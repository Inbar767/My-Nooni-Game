#include "StateMachine.h"

//Gets a State and a bool value and tells StateMachine to add it
void StateMachine::addState(StateRef newState, bool isReplacing)
{
	this->isAdding = true;
	this->isReplacing = isReplacing;
	this->newState = std::move(newState);
}

//Tells StateMachine to remove top State of states
void StateMachine::removeState()
{
	isRemoving = true;
}

//Process the changes of adding and removing
void StateMachine::processStateChanges()
{
	if (isRemoving && !states.empty()) //In case of removing current State
	{
		states.pop();
		if (!states.empty())
		{
			states.top()->resume();
		}
		isRemoving = false;
	}
	if (isAdding) //In case of adding newState
	{
		if (!states.empty())
		{
			if (isReplacing)
			{
				states.pop();
			}
			else
			{
				states.top()->pause();
			}
		}
		states.push(std::move(newState));
		states.top()->init();
		states.top()->resume();
		isAdding = false;
	}
}

//Gets the current State
StateRef& StateMachine::getCurrentState()
{
	return states.top();
}