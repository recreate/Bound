#ifndef _MENULABEL_H_
#define _MENULABEL_H_

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "globals.h"
#include "StateManager.h"
#include "ApplicationState.h"
#include "MenuItem.h"
#include "Screen.h"

class MenuLabel : public MenuItem {
public:
	MenuLabel(SDL_Surface* image);
	virtual ~MenuLabel();
	
	virtual void draw();
	virtual void highlight(bool set);
	virtual void action();
	
	virtual glm::vec2 getPosition();
	virtual float getWidth();
	virtual float getHeight();
	
	virtual void scale(float x, float y, float z);
	virtual void translate(float x, float y, float z);
	
protected:
	Screen* m_buttonImage;
};

#endif // _MENULABEL_H_
