#include "MenuState.h"

#include <stdio.h>

MenuState::MenuState(Screen* bg, GameMenu* menu) {
	m_background = bg;
	m_menu = menu;
}

MenuState::~MenuState() {}

void MenuState::setBackground(Screen* bg) {
	delete m_background;
	m_background = bg;
}

void MenuState::setMenu(GameMenu* menu) {
	delete m_menu;
	m_menu = menu;
}

void MenuState::handleEvent(SDL_Event e) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		g_stateManager->unloadCurrentState();
}

void MenuState::render() {
	m_background->draw();
	m_menu->draw();
}
