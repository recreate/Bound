#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "glew.h"

#include "util.h"
#include "StateManager.h"
#include "SplashScreenState.h"

#define WINDOW_TITLE "Bound"
#define VERTEX_SHADER "./src/VertexShader.glsl"
#define FRAGMENT_SHADER "./src/FragmentShader.glsl"

void initSDL(struct config* cfg);
void initGLEW();
void init();
void cleanup();
void render();
void mainLoop();
GLchar* readShaderFile(const char* filename);
void loadShaders();

extern SDL_Window* g_mainWindow;
extern SDL_GLContext g_mainContext;

extern StateManager* g_stateManager;

extern int g_windowWidth;
extern int g_windowHeight;
extern bool g_quit;

#endif // _MAIN_H_
