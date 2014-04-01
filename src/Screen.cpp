#include "Screen.h"

Screen::Screen(const char* imageFile) {
	m_programId = glCreateProgram();
	loadShaders(SCREEN_VSHADER, SCREEN_FSHADER);
	
	glBindAttribLocation(m_programId, ATTRIB_IN_POSITION_ID, "in_Position");
	glBindAttribLocation(m_programId, ATTRIB_IN_TEXCOORD_ID, "in_TexCoord");
	glBindFragDataLocation(m_programId, 0, "out_Color");
	
	glLinkProgram(m_programId);
	glUseProgram(m_programId);
	
	m_numVertices = 6;
	
	glm::vec4 vertices[6] = {
		SCREEN_VERTICES[0],
		SCREEN_VERTICES[1],
		SCREEN_VERTICES[3],
		SCREEN_VERTICES[3],
		SCREEN_VERTICES[1],
		SCREEN_VERTICES[2]
	};
	
	glm::vec2 textureCoords[6] = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f)
	};
	
	m_vao = (GLuint*)malloc(1*sizeof(GLuint));
	glGenVertexArrays(1, m_vao);
	glBindVertexArray(*m_vao);
	
	m_vbo = (GLuint*)malloc(2*sizeof(GLuint));
	glGenBuffers(2, m_vbo);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]); // vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_numVertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIB_IN_POSITION_ID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATTRIB_IN_POSITION_ID);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]); // texture coordinates
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_numVertices, textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIB_IN_TEXCOORD_ID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATTRIB_IN_TEXCOORD_ID);
	
	m_screenColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glUniform4fv(glGetUniformLocation(m_programId, "uColor"), 1, glm::value_ptr(m_screenColor));
	
	m_textureObject = (GLuint*)malloc(1*sizeof(GLuint));
	glGenTextures(1, m_textureObject);
	glBindTexture(GL_TEXTURE_2D, *m_textureObject);
	
	SDL_Surface* logo = SDL_LoadBMP(imageFile);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo->w, logo->h, 0, GL_RGB, GL_UNSIGNED_BYTE, logo->pixels);
	glUniform1i(glGetUniformLocation(m_programId, "uTexture"), 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Screen::~Screen() {
	free(m_vao);
	free(m_vbo);
	free(m_textureObject);
}

void Screen::setScreenColor(glm::vec4 color) {
	m_screenColor = color;
	glUniform4fv(glGetUniformLocation(m_programId, "uColor"), 1, glm::value_ptr(m_screenColor));
}

void Screen::draw() {
	glBindVertexArray(m_vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
}
