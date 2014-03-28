#include "StateManager.h"

StateManager::StateManager() {}
StateManager::~StateManager() {}

ApplicationState* StateManager::getCurrentState() {
	if (!m_states.empty())
		return m_states.top();
	return NULL;
}

void StateManager::loadNewCurrentState(ApplicationState* s) {
	m_states.push(s);
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
