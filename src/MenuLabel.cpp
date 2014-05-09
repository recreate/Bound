#include "MenuLabel.h"

MenuLabel::MenuLabel(SDL_Surface* image, SDL_Surface* text) {
	m_buttonImage = new Screen(image);
	m_buttonText = new Screen(text);
	
	m_buttonImage->translate(0.0f, 0.0f, 0.7f);
	m_buttonText->translate(0.0f, 0.0f, 0.6f);
}

MenuLabel::~MenuLabel() {
	printf("MenuButton destructor\n");
	
	delete m_buttonImage;
	delete m_buttonText;
}

void MenuLabel::scale(float x, float y, float z) {
	m_buttonImage->scale(x, y, z);
	m_buttonText->scale(x, y, z);
}

void MenuLabel::translate(float x, float y, float z) {
	m_buttonImage->translate(x, y, z);
	m_buttonText->translate(x, y, z);
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
	m_buttonText->draw();
}
