#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#include <vector>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "Screen.h"
#include "DrawableEntity.h"

class GameMenu : public DrawableEntity {
public:
	GameMenu();
	~GameMenu();
	
	virtual void draw();
	
	void appendMenuOption(Screen* option);
	
protected:
	// TODO: Remove MenuItem.cpp and replace with this?
	std::vector<Screen*> m_menuOptions;
};

#endif //_GAMEMENU_H_
