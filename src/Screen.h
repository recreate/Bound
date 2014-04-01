#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "DrawableEntity.h"

#define SCREEN_VSHADER "./src/shaders/ScreenVertexShader.glsl"
#define SCREEN_FSHADER "./src/shaders/ScreenFragmentShader.glsl"

#define ATTRIB_IN_POSITION_ID 0
#define ATTRIB_IN_TEXCOORD_ID 1

class Screen : public DrawableEntity {
public:
	Screen(const char* imageFile);
	virtual ~Screen();
	
	virtual void draw();
	void setScreenColor(glm::vec4 color);
	
private:
	glm::vec4 SCREEN_VERTICES[4] = {
		glm::vec4(-1.0f,  1.0f, -0.1f, 1.0f), // top left
		glm::vec4(-1.0f, -1.0f, -0.1f, 1.0f), // bottom left
		glm::vec4( 1.0f, -1.0f, -0.1f, 1.0f), // bottom right
		glm::vec4( 1.0f,  1.0f, -0.1f, 1.0f)  // top right
	};
	
	glm::vec4 m_screenColor;
};

#endif // _SCREEN_H_
