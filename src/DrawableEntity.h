#ifndef _DRAWABLEENTITY_H_
#define _DRAWABLEENTITY_H_

#include <glm/glm.hpp>
#include "glew.h"

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
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec4* m_vertices;
	glm::vec3* m_normals;
	glm::vec2* m_textureCoords;
	bool m_needsUpdate;
	
	GLuint* m_vao; // vertex array object
	GLuint* m_vbo; // vertex buffer object
	GLuint* m_textureObject;
	GLuint* m_textureBuffer;
};

#endif // _DRAWABLEENTITY_H_
