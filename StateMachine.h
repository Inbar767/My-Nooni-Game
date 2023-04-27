#include "State.h"
#include <memory>
#include <stack>

typedef std::unique_ptr <State> StateRef; //Pointer to a State

//A class to control States behavior
class StateMachine
{
public:
	//Constructor
	StateMachine() { }
	//Destructor
	~StateMachine() { }
	//Gets a State and a bool value and tells StateMachine to add it
	void addState(StateRef newState, bool isReplacing = true);
	//Tells StateMachine to remove top State of states
	void removeState();
	//Process the changes of adding and removing
	void processStateChanges();
	//Gets the current State
	StateRef& getCurrentState();

private:
	std::stack <StateRef> states; //Holds all States
	StateRef newState;

	bool isRemoving;
	bool isAdding;
	bool isReplacing;
};

