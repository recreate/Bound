#ifndef _MENUBUTTON_H_
#define _MENUBUTTON_H_

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "globals.h"
#include "StateManager.h"
#include "ApplicationState.h"
#include "MenuItem.h"
#include "MenuLabel.h"
#include "Screen.h"

class MenuButton : public MenuLabel {
public:
	MenuButton(SDL_Surface* image, SDL_Surface* text, ApplicationState* state);
	virtual ~MenuButton();
	
	virtual void highlight(bool set);
	virtual void action();
	
protected:
	ApplicationState* m_state;
};

#endif // _MENUBUTTON_H_
