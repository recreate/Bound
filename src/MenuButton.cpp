#include "MenuButton.h"

MenuButton::MenuButton(SDL_Surface* image, SDL_Surface* text, ApplicationState* state) 
	: MenuLabel::MenuLabel(image, text)
{
	m_state = state;
}

MenuButton::~MenuButton() {
	printf("MenuButton destructor\n");
}

void MenuButton::highlight(bool set) {
	if (set)
		m_buttonImage->setScreenColor(glm::vec4(1.5f, 1.5f, 1.5f, 1.0f));
	else
		m_buttonImage->setScreenColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void MenuButton::action() {
	if (m_state == NULL)
		g_stateManager->unloadCurrentState();
	else
		g_stateManager->loadNewCurrentState(m_state);
}
