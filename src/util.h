#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <string.h>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "globals.h"

// Aspect ratio 16:9
#define ASPECT_RATIO_WIDTH 1920
#define ASPECT_RATIO_HEIGHT 1080

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
void printMat4(glm::mat4 matrix);

#endif // _UTIL_H_
