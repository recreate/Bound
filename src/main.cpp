#include "glew.h"
#include <SDL2/SDL.h>

#include <string>
#include <stdlib.h>
#include <stdio.h>

void check_error(int condition, const char* msg) {
	if (condition) {
		fprintf(stdout, "Error: %s\n", msg);
		exit(1);
	}
}

int main(int argc, char* argv[]) {
	int status;
	
	SDL_Window* mainWindow;
	SDL_GLContext mainContext;
	
	status = SDL_Init(SDL_INIT_VIDEO);
	check_error(status != 0, SDL_GetError());
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	
	mainWindow = SDL_CreateWindow("openGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	check_error(mainWindow == NULL, SDL_GetError());
	
	mainContext = SDL_GL_CreateContext(mainWindow);
	check_error(mainContext == NULL, SDL_GetError());
	
	GLenum err = glewInit();
	check_error(err != GLEW_OK, (char*)glewGetErrorString(err));
	
	SDL_Event e;
	while(true) {
		while( SDL_WaitEvent(&e) ) {
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				exit(0);
		}
	}
	
	SDL_Quit();
	
	return 0;
}
