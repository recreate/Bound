#include "GameMenu.h"

GameMenu::GameMenu() {
}

GameMenu::~GameMenu() {}

void GameMenu::appendMenuOption(Screen* option) {
	m_menuOptions.push_back(option);
}

void GameMenu::draw() {
	for (std::vector<Screen*>::iterator iter = m_menuOptions.begin(); iter != m_menuOptions.end(); iter++) {
		
	}
}
