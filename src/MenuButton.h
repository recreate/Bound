#ifndef _MENUBUTTON_H_
#define _MENUBUTTON_H_

#include <SDL2/SDL.h>

#include "globals.h"
#include "StateManager.h"
#include "ApplicationState.h"
#include "MenuItem.h"
#include "Screen.h"

class MenuButton : public MenuItem {
public:
	MenuButton(SDL_Surface* image);
	virtual ~MenuButton();
	
	virtual void draw();
	virtual void action();
	
	virtual glm::vec2 getPosition();
	virtual float getWidth();
	virtual float getHeight();
	
	virtual void scale(float x, float y, float z);
	virtual void translate(float x, float y, float z);
	
	void setTransitionState(ApplicationState* state);
	
protected:
	Screen* m_buttonImage;
	ApplicationState* m_state;
};

#endif // _MENUBUTTON_H_
