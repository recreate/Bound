#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_

#include <SDL2/SDL.h>

#include "globals.h"
#include "StateManager.h"
#include "Screen.h"
#include "GameMenu.h"
#include "ApplicationState.h"

class MenuState : public ApplicationState {
public:
	MenuState(SDL_Surface* image, GameMenu* menu);
	virtual ~MenuState();
	
	virtual void handleEvent(SDL_Event e);
	virtual void render();
	
	void setBackground(Screen* bg);
	void setMenu(GameMenu* menu);
	
private:
	Screen* m_background;
	GameMenu* m_menu;
};

#endif // _MENUSTATE_H_
