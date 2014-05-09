#include "MenuLabel.h"

MenuLabel::MenuLabel(SDL_Surface* image) {
	m_buttonImage = new Screen(image);
}

MenuLabel::~MenuLabel() {
	printf("MenuButton destructor\n");
	
	delete m_buttonImage;
}

void MenuLabel::scale(float x, float y, float z) {
	m_buttonImage->scale(x, y, z);
}

void MenuLabel::translate(float x, float y, float z) {
	m_buttonImage->translate(x, y, z);
}

// Gets the x and y position of the menu button
glm::vec2 MenuLabel::getPosition() {
	glm::mat4 trans = m_buttonImage->getTranslations();
	return glm::vec2(trans[3][0], trans[3][1]);
}

float MenuLabel::getWidth() {
	return m_buttonImage->getWidth();
}

float MenuLabel::getHeight() {
	return m_buttonImage->getHeight();
}

void MenuLabel::highlight(bool set) {}

void MenuLabel::action() {}

void MenuLabel::draw() {
	m_buttonImage->draw();
}
