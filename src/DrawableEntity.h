#ifndef _DRAWABLEENTITY_H_
#define _DRAWABLEENTITY_H_

#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "glew.h"

#define UNIFORM_MODEL "uModelMatrix"
#define UNIFORM_VIEW "uViewMatrix"
#define UNIFORM_PROJ "uProjectionMatrix"

class DrawableEntity {
public:
	DrawableEntity();
	virtual ~DrawableEntity();
	
	virtual void draw();
	
	virtual void rotate();
	virtual void scale(float x, float y, float z);
	virtual void translate(float x, float y, float z);
	virtual void setPosition(float x, float y, float z);
	
protected:
	GLchar* readShaderFile(const char* filename); // TODO: make private?
	void loadShaders(const char* vertexShader, const char* fragmentShader);
	
	GLuint m_vertexShaderId;
	GLuint m_fragmentShaderId;
	GLuint m_programId;
	
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_proj;
	
	// TODO: Move into subclasses?
	size_t m_numVertices;
	glm::vec4* m_vertices;
	glm::vec3* m_normals;
	glm::vec4* m_colors;
	glm::vec2* m_textureCoords;
	
	GLuint* m_vao; // vertex array object
	GLuint* m_textureObject;
	
	GLuint* m_VBOVertices;
	GLuint* m_VBONormals;
	GLuint* m_VBOColors;
	GLuint* m_VBOTextureCoords;
};

#endif // _DRAWABLEENTITY_H_
