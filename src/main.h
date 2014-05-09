#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "glew.h"

#include "globals.h"
#include "util.h"
#include "ThreeDModel.h"
#include "StateManager.h"
#include "SplashScreenState.h"
#include "MenuState.h"
#include "GameMenu.h"
#include "MenuItem.h"
#include "MenuButton.h"
#include "GameTimer.h"

#define WINDOW_TITLE "Bound"
#define VERTEX_SHADER "./src/VertexShader.glsl"
#define FRAGMENT_SHADER "./src/FragmentShader.glsl"

void initSDL(struct config* cfg);
void initGLEW();
void init();
void cleanup();
void render();
void mainLoop();

#endif // _MAIN_H_
