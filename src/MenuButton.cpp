#include "MenuButton.h"

MenuButton::MenuButton(SDL_Surface* image) {
	m_buttonImage = new Screen(image);
	m_state = NULL;
}

MenuButton::~MenuButton() {
	printf("MenuButton destructor\n");
	
	delete m_buttonImage;
	//delete m_state;
}

void MenuButton::scale(float x, float y, float z) {
	m_buttonImage->scale(x, y, z);
}

void MenuButton::translate(float x, float y, float z) {
	m_buttonImage->translate(x, y, z);
}

void MenuButton::setTransitionState(ApplicationState* state) {
	m_state = state;
}

// Gets the x and y position of the menu button
glm::vec2 MenuButton::getPosition() {
	glm::mat4 model = m_buttonImage->getTranslations();
	return glm::vec2(model[3][0], model[3][1]);
}

float MenuButton::getWidth() {
	return m_buttonImage->getWidth();
}

float MenuButton::getHeight() {
	return m_buttonImage->getHeight();
}

void MenuButton::action() {
	if (m_state == NULL)
		g_stateManager->unloadCurrentState();
	else
		g_stateManager->loadNewCurrentState(m_state);
}

void MenuButton::draw() {
	m_buttonImage->draw();
}
