#ifndef _SPLASHSCREENSTATE_H_
#define _SPLASHSCREENSTATE_H_

#include "main.h"
#include "ApplicationState.h"
#include "Screen.h"

class SplashScreenState : public ApplicationState {
public:
	SplashScreenState();
	virtual ~SplashScreenState();
	
	virtual void handleEvent(SDL_Event e);
	virtual void render();
	
private:
	Screen* m_splashScreen;
};

#endif // _SPLASHSCREENSTATE_H_
