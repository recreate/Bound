#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "globals.h"

#define CONFIGURATION_FILE "settings.cfg"
#define DEFAULT_FULLSCREEN 1
#define DEFAULT_BORDER 0

struct config {
	int height;
	int width;
	bool fullscreen;
	bool border;
};

void check_error(int condition, const char* msg);
struct config* getConfiguration();
SDL_Surface* loadTexture(const char* filename);

#endif // _UTIL_H_
