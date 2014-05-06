#include "ApplicationState.h"

ApplicationState::ApplicationState() {}
ApplicationState::~ApplicationState() {
	printf("ApplicationState destructor\n");
}

void ApplicationState::handleEvent(SDL_Event e) {}
void ApplicationState::render() {}
