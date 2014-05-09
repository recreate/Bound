#include "GameMenu.h"

GameMenu::GameMenu(SDL_Surface* image, unsigned int rows, unsigned int cols) {
	m_backdrop = new Screen(image);
	m_backdrop->translate(0.0f, 0.0f, 0.8f);
	m_rows = rows;
	m_cols = cols;
	
	m_menuOptions = (MenuItem***)malloc(m_cols * sizeof(MenuItem**));
	for (int i = 0; i < m_cols; i++) {
		m_menuOptions[i] = (MenuItem**)malloc(m_rows * sizeof(MenuItem*));
		for (int j = 0; j < m_rows; j++) {
			m_menuOptions[i][j] = NULL;
		}
	}
}

GameMenu::~GameMenu() {
	printf("GameMenu destructor\n");
	
	delete m_backdrop;
	
	for (int i = 0; i < m_cols; i++) {
		for (int j = 0; j < m_rows; j++) {
			if (m_menuOptions[i][j] != NULL) {
				delete (m_menuOptions[i][j]);
			}
		}
		free(m_menuOptions[i]);
	}
	free(m_menuOptions);
}

// Origin is at top left corner of m_backdrop
void GameMenu::addMenuOption(MenuItem* option, int x, int y) {
	float cellWidth = m_backdrop->getWidth()/m_cols;
	float cellHeight = m_backdrop->getHeight()/m_rows;
	
	if (x < m_cols && y < m_rows) {
		if (m_menuOptions[x][y] != NULL)
			delete m_menuOptions[x][y];
		
		option->translate(-m_backdrop->getWidth()/2.0f, m_backdrop->getHeight()/2.0f, 0.0f);
		option->translate(cellWidth/2.0f, -cellHeight/2.0f, 0.0f);
		option->translate(x * cellWidth, -y * cellHeight, 0.0f);
		
		m_menuOptions[x][y] = option;
	}
}

// TODO: Fix event handling with respect to scaled menu buttons
void GameMenu::handleEvent(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION) {
		int windowHeight, windowWidth;
		SDL_GetWindowSize(g_mainWindow, &windowWidth, &windowHeight);
		
		// Convert SDL window coordinates to OpenGL device coordinates
		float screenX = (event.button.x/(float)windowWidth - 0.5f) * 2.0f;
		float screenY = (0.5f - event.button.y/(float)windowHeight) * 2.0f;
		
		for (int i = 0; i < m_cols; i++) {
			for (int j = 0; j < m_rows; j++) {
				if (m_menuOptions[i][j] == NULL)
					continue;
				
				float posX = m_menuOptions[i][j]->getPosition().x * g_horizontalPlusScale;
				float posY = m_menuOptions[i][j]->getPosition().y * g_horizontalPlusScale;
				float width = m_menuOptions[i][j]->getWidth() * g_horizontalPlusScale;
				float height = m_menuOptions[i][j]->getHeight() * g_horizontalPlusScale;
				
				m_menuOptions[i][j]->highlight(false);
				if ((screenX >= posX - width/2.0f && screenX <= posX + width/2.0f) && (screenY >= posY - height/2.0f && screenY <= posY + height/2.0f)) {
					if (event.type == SDL_MOUSEMOTION)
						m_menuOptions[i][j]->highlight(true);
					if (event.type == SDL_MOUSEBUTTONDOWN)
						m_menuOptions[i][j]->action();
					return;
				}
			}
		}
	}
}

void GameMenu::draw() {
	m_backdrop->draw();
	
	for (int i = 0; i < m_cols; i++)
		for (int j = 0; j < m_rows; j++)
			if (m_menuOptions[i][j] != NULL) {
				m_menuOptions[i][j]->draw();
			}
}
