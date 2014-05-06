#include "DrawableEntity.h"

DrawableEntity::DrawableEntity() {
	m_translations = glm::mat4();
	m_rotations = glm::mat4();
	m_scalings = glm::mat4();
	
	m_vertices = NULL;
	m_normals = NULL;
	m_colors = NULL;
	m_textureCoords = NULL;
	
	m_vao = NULL;
	m_textureObject = NULL;
	
	m_VBOVertices = NULL;
	m_VBONormals = NULL;
	m_VBOColors = NULL;
	m_VBOTextureCoords = NULL;
}

DrawableEntity::~DrawableEntity() {
	printf("DrawableEntity destructor\n");

	free(m_vao);
	free(m_textureObject);
	free(m_VBOVertices);
	free(m_VBONormals);
	free(m_VBOColors);
	free(m_VBOTextureCoords);
}

// TODO ??? //
void DrawableEntity::rotate() {}

void DrawableEntity::scale(float x, float y, float z) {
	glUseProgram(m_programId);
	m_scalings = glm::scale(m_scalings, glm::vec3(x,y,z));
	m_model = glm::scale(m_model, glm::vec3(x,y,z));
	glUniformMatrix4fv(glGetUniformLocation(m_programId, UNIFORM_MODEL), 1, GL_FALSE, glm::value_ptr(m_model));
}

void DrawableEntity::translate(float x, float y, float z) {
	glUseProgram(m_programId);
	m_translations = glm::translate(m_translations, glm::vec3(x,y,z));
	m_model = glm::translate(m_model, glm::vec3(x,y,z));
	glUniformMatrix4fv(glGetUniformLocation(m_programId, UNIFORM_MODEL), 1, GL_FALSE, glm::value_ptr(m_model));
}

void DrawableEntity::setPosition(float x, float y, float z) {}

glm::mat4 DrawableEntity::getTranslations() {
	return m_translations;
}

glm::mat4 DrawableEntity::getRotations() {
	return m_rotations;
}

glm::mat4 DrawableEntity::getScalings() {
	return m_scalings;
}


void DrawableEntity::draw() {}

GLchar* DrawableEntity::readShaderFile(const char* filename) {
	FILE* f;
	long fileSize;
	GLchar* buf;
	size_t nread;
	
	f = fopen(filename, "rb");
	
	fseek(f, 0, SEEK_END);
	fileSize = ftell(f);
	rewind(f);
	
	buf = (GLchar*)malloc((fileSize+1) * sizeof(GLchar));
	nread = fread(buf, sizeof(GLchar), fileSize, f);
	buf[nread] = '\0';
	
	fclose(f);
	return buf;
}

void DrawableEntity::loadShaders(const char* vertexShader, const char* fragmentShader) {
	GLint status;
	
	char* vShader = readShaderFile(vertexShader);
	m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShaderId, 1, (const GLchar**)(&vShader), NULL);
	glCompileShader(m_vertexShaderId);
	glGetShaderiv(m_vertexShaderId, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
		fprintf(stderr, "Failed to compile vertex shader\n");
	
	char* fShader = readShaderFile(fragmentShader);
	m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShaderId, 1, (const GLchar**)(&fShader), NULL);
	glCompileShader(m_fragmentShaderId);
	glGetShaderiv(m_fragmentShaderId, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
		fprintf(stderr, "Failed to compile fragment shader\n");
	
	glAttachShader(m_programId, m_vertexShaderId);
	glAttachShader(m_programId, m_fragmentShaderId);
	
	free(vShader);
	free(fShader);
}
