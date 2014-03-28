#include "SplashScreenState.h"

SplashScreenState::SplashScreenState() {
	m_splashScreen = new Screen();
}
SplashScreenState::~SplashScreenState() {
	delete m_splashScreen;
}

void SplashScreenState::handleEvent(SDL_Event e) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		g_stateManager->unloadCurrentState();
}

void SplashScreenState::render() {
	m_splashScreen->draw();
}
