#include "Screen.h"

Screen::Screen(SDL_Surface* image) {
	m_programId = glCreateProgram();
	loadShaders(SCREEN_VSHADER, SCREEN_FSHADER);
	
	m_vao = (GLuint*)malloc(1*sizeof(GLuint));
	glGenVertexArrays(1, m_vao);
	glBindVertexArray(*m_vao);
	
	glBindAttribLocation(m_programId, ATTRIB_IN_POSITION_ID, "in_Position");
	glBindAttribLocation(m_programId, ATTRIB_IN_TEXCOORD_ID, "in_TexCoord");
	glBindFragDataLocation(m_programId, 0, "out_Color");
	
	glLinkProgram(m_programId);
	glUseProgram(m_programId);
	
	int windowHeight, windowWidth;
	SDL_GetWindowSize(g_mainWindow, &windowHeight, &windowWidth);
	
	float ww = (float)(image->w)/windowHeight;
	float hh = (float)(image->h)/windowWidth;
	
	glm::vec4 box[4] = {
		glm::vec4(-ww,  hh, -0.1f, 1.0f), // top left
		glm::vec4(-ww, -hh, -0.1f, 1.0f), // bottom left
		glm::vec4( ww, -hh, -0.1f, 1.0f), // bottom right
		glm::vec4( ww,  hh, -0.1f, 1.0f)  // top right
	};
	
	m_numVertices = 6;
	glm::vec4 vertices[6] = {
		box[0], // top left
		box[1], // bottom left
		box[3], // top right
		box[3], // top right
		box[1], // bottom left
		box[2]  // bottom right
	};
	
	glm::vec2 textureCoords[6] = {
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f)
	};
	
	m_VBOVertices = (GLuint*)malloc(1*sizeof(GLuint));
	glGenBuffers(1, m_VBOVertices);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices[0]); // vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_numVertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIB_IN_POSITION_ID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATTRIB_IN_POSITION_ID);
	
	m_VBOTextureCoords = (GLuint*)malloc(1*sizeof(GLuint));
	glGenBuffers(1, m_VBOTextureCoords);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextureCoords[0]); // texture coordinates
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_numVertices, textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIB_IN_TEXCOORD_ID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATTRIB_IN_TEXCOORD_ID);
	
	m_screenColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glUniform4fv(glGetUniformLocation(m_programId, "uColor"), 1, glm::value_ptr(m_screenColor));
	
	m_textureObject = (GLuint*)malloc(1*sizeof(GLuint));
	glGenTextures(1, m_textureObject);
	glBindTexture(GL_TEXTURE_2D, *m_textureObject);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, image->pixels);
	glUniform1i(glGetUniformLocation(m_programId, "uTexture"), 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	m_model = glm::mat4();
	m_view = glm::mat4();
	m_proj = glm::mat4();
	glUniformMatrix4fv(glGetUniformLocation(m_programId, UNIFORM_MODEL), 1, GL_FALSE, glm::value_ptr(m_model));
	glUniformMatrix4fv(glGetUniformLocation(m_programId, UNIFORM_VIEW), 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(glGetUniformLocation(m_programId, UNIFORM_PROJ), 1, GL_FALSE, glm::value_ptr(m_proj));
}

Screen::~Screen() {
	free(m_vao);
	free(m_VBOVertices);
	free(m_VBOTextureCoords);
	free(m_textureObject);
}

void Screen::setScreenColor(glm::vec4 color) {
	m_screenColor = color;
	glUniform4fv(glGetUniformLocation(m_programId, "uColor"), 1, glm::value_ptr(m_screenColor));
}

void Screen::draw() {
	glBindVertexArray(m_vao[0]);
	glBindTexture(GL_TEXTURE_2D, *m_textureObject);
	glUseProgram(m_programId);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
}
