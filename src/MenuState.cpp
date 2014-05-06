#include "MenuState.h"

#include <stdio.h>

MenuState::MenuState(SDL_Surface* image, GameMenu* menu) {
	m_background = new Screen(image);
	m_background->translate(0.0f, 0.0f, 0.9f);
	m_menu = menu;
}

MenuState::~MenuState() {
	printf("MenuState destructor\n");
	
	delete m_background;
	delete m_menu;
}

void MenuState::setBackground(Screen* bg) {
	delete m_background;
	m_background = bg;
}

void MenuState::setMenu(GameMenu* menu) {
	delete m_menu;
	m_menu = menu;
}

void MenuState::handleEvent(SDL_Event e) {
	m_menu->handleEvent(e);
	
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		g_stateManager->unloadCurrentState();
}

void MenuState::render() {
	m_background->draw();
	m_menu->draw();
}
