#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#include <vector>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "globals.h"
#include "DrawableEntity.h"
#include "Screen.h"
#include "MenuItem.h"

class GameMenu : public DrawableEntity {
public:
	GameMenu(SDL_Surface* image, unsigned int rows, unsigned int cols);
	virtual ~GameMenu();
	
	virtual void draw();
	virtual void handleEvent(SDL_Event event);
	
	void setBackdrop(Screen* backdrop);
	void addMenuOption(MenuItem* option, int x, int y);
	
protected:
	
	unsigned int m_rows;
	unsigned int m_cols;
	Screen* m_backdrop;
	MenuItem*** m_menuOptions;
};

#endif //_GAMEMENU_H_
