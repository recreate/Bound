#include "SplashScreenState.h"

SplashScreenState::SplashScreenState(SDL_Surface* image, unsigned int duration, unsigned int fadeIn, unsigned int fadeOut) {
	m_splashScreen = new Screen(image);
	m_timer = new GameTimer();
	
	m_duration = duration;
	m_fadeInDuration = fadeIn;
	m_fadeOutDuration = fadeOut;
}
SplashScreenState::~SplashScreenState() {
	printf("SplashScreenState destructor\n");
	delete m_splashScreen;
	delete m_timer;
}

void SplashScreenState::handleEvent(SDL_Event e) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		g_stateManager->unloadCurrentState();
}

void SplashScreenState::render() {
	m_timer->start();
	
	unsigned int elapsedTime = m_timer->getElapsedTime();
	if (m_timer->getElapsedTime() >= m_duration) {
		g_stateManager->unloadCurrentState();
		return;
	} else if (elapsedTime <= m_fadeInDuration) {
		float v = (float)(elapsedTime)/(m_fadeInDuration);
		m_splashScreen->setScreenColor(glm::vec4(v, v, v, 1.0));
	} else if (elapsedTime >= m_duration - m_fadeOutDuration) {
		float v = (float)(m_duration-elapsedTime)/(m_fadeOutDuration);
		m_splashScreen->setScreenColor(glm::vec4(v, v, v, 1.0));
	}
	
	m_splashScreen->draw();
}
