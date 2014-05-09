#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <SDL2/SDL.h>

class StateManager;

extern SDL_Window* g_mainWindow;
extern SDL_GLContext g_mainContext;

extern StateManager* g_stateManager;

extern float g_horizontalPlusScale;
extern int g_windowWidth;
extern int g_windowHeight;
extern bool g_quit;

#endif // _GLOBALS_H_
