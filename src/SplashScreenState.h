#ifndef _SPLASHSCREENSTATE_H_
#define _SPLASHSCREENSTATE_H_

#include "main.h"
#include "ApplicationState.h"
#include "Screen.h"
#include "GameTimer.h"

class SplashScreenState : public ApplicationState {
public:
	SplashScreenState(const char* imageFile, unsigned int duration, unsigned int fadeIn, unsigned int fadeOut);
	virtual ~SplashScreenState();
	
	virtual void handleEvent(SDL_Event e);
	virtual void render();
	
private:
	Screen* m_splashScreen;
	GameTimer* m_timer;
	
	unsigned int m_duration; // splash screen duration in milliseconds
	unsigned int m_fadeInDuration;
	unsigned int m_fadeOutDuration;
};

#endif // _SPLASHSCREENSTATE_H_
