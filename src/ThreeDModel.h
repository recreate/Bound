#ifndef _3DMODEL_
#define _3DMODEL_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "glew.h"

#include "util.h"
#include "DrawableEntity.h"
#include "ObjParser.h"

#define MODEL_VSHADER "./src/shaders/3DModelVertexShader.glsl"
#define MODEL_FSHADER "./src/shaders/3DModelFragmentShader.glsl"

#define TDMODEL_ATTRIB_IN_POSITION_ID 0
#define TDMODEL_ATTRIB_IN_NORMAL_ID 1
#define TDMODEL_ATTRIB_IN_TEXCOORD_ID 2

class ThreeDModel : public DrawableEntity {
public:
	ThreeDModel(const char* baseDir, const char* modelFile);
	~ThreeDModel();
	
	void draw();
	
private:
	ObjParser* m_parser;
};

#endif //_3DMODEL_
