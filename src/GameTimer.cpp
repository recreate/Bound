#include "GameTimer.h"

GameTimer::GameTimer() {
	m_isStarted = false;
	m_startTime = 0;
	m_stopTime = 0;
}

GameTimer::~GameTimer() {}

void GameTimer::start() {
	if (m_isStarted)
		return;
	
	m_startTime = SDL_GetTicks() - m_stopTime;
	m_isStarted = true;
}

void GameTimer::stop() {
	m_stopTime += SDL_GetTicks() - m_startTime;
	m_isStarted = false;
}

void GameTimer::restart() {
	m_startTime = SDL_GetTicks();
	m_stopTime = 0;
	m_isStarted = true;
}

unsigned int GameTimer::getElapsedTime() {
	return SDL_GetTicks() - m_startTime;
}
