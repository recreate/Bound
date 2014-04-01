#ifndef _DRAWABLEENTITY_H_
#define _DRAWABLEENTITY_H_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include "glew.h"

#include <stdio.h>

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
	GLchar* readShaderFile(const char* filename);
	void loadShaders(const char* vertexShader, const char* fragmentShader);
	
	GLuint m_vertexShaderId;
	GLuint m_fragmentShaderId;
	GLuint m_programId;
	
	size_t m_numVertices;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	
	glm::vec4* m_vertices;
	glm::vec4* m_colors;
	glm::vec3* m_normals;
	glm::vec2* m_textureCoords;
	bool m_needsUpdate;
	
	GLuint* m_vao; // vertex array object
	GLuint* m_vbo; // vertex buffer object
	GLuint* m_textureObject;
};

#endif // _DRAWABLEENTITY_H_
