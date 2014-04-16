#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include <stack>

#include "ApplicationState.h"

class StateManager {
public:
	StateManager();
	~StateManager();
	
	ApplicationState* getCurrentState();
	void loadNewCurrentState(ApplicationState* s);
	void unloadCurrentState();
	void clearAllStates();
	bool hasState();
	
private:
	// TODO: Replace with std::vector?
	// TOOD: Add data member to ApplicationState to allow for rendering previous state?
	std::stack<ApplicationState*> m_states;
};

#endif // _STATEMANAGER_H_