#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include <vector>
#include <stack>

#include "util.h"
#include "ApplicationState.h"

// TODO: Maybe have applications states register to the StateManager to manage deleting resources?
class StateManager {
public:
	StateManager();
	~StateManager();
	
	void registerState(ApplicationState* s);
	void loadNewCurrentState(ApplicationState* s);
	ApplicationState* getCurrentState();
	void unloadCurrentState();
	void clearAllStates();
	bool hasState();
	
private:
	
	// TOOD: Add data member to ApplicationState to allow for rendering previous state?
	std::vector<ApplicationState*> m_registeredStates;
	// TODO: Replace with std::vector?
	std::stack<ApplicationState*> m_states;
};

#endif // _STATEMANAGER_H_