#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "globals.h"
#include "util.h"
#include "DrawableEntity.h"

#define SCREEN_VSHADER "./src/shaders/ScreenVertexShader.glsl"
#define SCREEN_FSHADER "./src/shaders/ScreenFragmentShader.glsl"

#define ATTRIB_IN_POSITION_ID 0
#define ATTRIB_IN_TEXCOORD_ID 1

class Screen : public DrawableEntity {
public:
	Screen(SDL_Surface* image);
	virtual ~Screen();
	
	virtual void draw();
	void setScreenColor(glm::vec4 color);
	
private:
	glm::vec4 m_screenColor;
};

#endif // _SCREEN_H_
