#include "StateManager.h"

StateManager::StateManager() {}
StateManager::~StateManager() {
	printf("StateManager destructor\n");
	
	clearAllStates();
	
	while(!m_registeredStates.empty()) {
		ApplicationState* state = m_registeredStates.back();
		m_registeredStates.pop_back();
		delete state;
	}
}

void StateManager::registerState(ApplicationState* s) {
	m_registeredStates.push_back(s);
}

void StateManager::loadNewCurrentState(ApplicationState* s) {
	m_states.push(s);
}

ApplicationState* StateManager::getCurrentState() {
	if (!m_states.empty())
		return m_states.top();
	return NULL;
}

void StateManager::unloadCurrentState() {
	if (!m_states.empty())
		m_states.pop();
}

void StateManager::clearAllStates() {
	while (!m_states.empty())
		m_states.pop();
}

bool StateManager::hasState() {
	return !m_states.empty();
}
