#ifndef _APPLICATIONSTATE_H_
#define _APPLICATIONSTATE_H_

#include <SDL2/SDL.h>

class ApplicationState {
public:
	ApplicationState();
	virtual ~ApplicationState();
	
	virtual void handleEvent(SDL_Event e);
	virtual void render();
	
private:

};

#endif // _APPLICATIONSTATE_H_
