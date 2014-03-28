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
	std::stack<ApplicationState*> m_states;
};

#endif // _STATEMANAGER_H_