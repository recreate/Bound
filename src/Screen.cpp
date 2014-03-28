#include "Screen.h"

Screen::Screen() {
	SCREEN_VERTICES = new glm::vec4[4];
	SCREEN_VERTICES[0] = glm::vec4(-0.5f,  0.5f, -0.1f, 1.0f); // top left
	SCREEN_VERTICES[1] = glm::vec4(-0.5f, -0.5f, -0.1f, 1.0f); // bottom left
	SCREEN_VERTICES[2] = glm::vec4( 0.5f, -0.5f, -0.1f, 1.0f); // bottom right
	SCREEN_VERTICES[3] = glm::vec4( 0.5f,  0.5f, -0.1f, 1.0f);  // top right
	
	m_vertices = new glm::vec4[6];
	m_vertices[0] = SCREEN_VERTICES[0];
	m_vertices[1] = SCREEN_VERTICES[1];
	m_vertices[2] = SCREEN_VERTICES[3];
	m_vertices[3] = SCREEN_VERTICES[3];
	m_vertices[4] = SCREEN_VERTICES[1];
	m_vertices[5] = SCREEN_VERTICES[2];
	
	glm::vec4 colors[6] = {
		glm::vec4(0.5f, 0.4f, 0.3f, 1.0f),
		glm::vec4(0.5f, 0.4f, 0.3f, 1.0f),
		glm::vec4(0.5f, 0.4f, 0.3f, 1.0f),
		glm::vec4(0.5f, 0.4f, 0.3f, 1.0f),
		glm::vec4(0.5f, 0.4f, 0.3f, 1.0f),
		glm::vec4(0.5f, 0.4f, 0.3f, 1.0f)
	};
	
	m_vao = new GLuint[1];
	glGenVertexArrays(1, m_vao);
	glBindVertexArray(m_vao[0]);
	
	m_vbo = new GLuint[1];
	glGenBuffers(1, &m_vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 12, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * 6, m_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 6, sizeof(glm::vec4) * 6, colors);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(sizeof(glm::vec4) * 6));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

Screen::~Screen() {}

void Screen::draw() {
	glBindVertexArray(m_vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
