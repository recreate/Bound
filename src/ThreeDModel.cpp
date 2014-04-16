#include "ThreeDModel.h"

ThreeDModel::ThreeDModel(const char* baseDir, const char* modelFile) {
	int windowHeight, windowWidth;
	SDL_GetWindowSize(g_mainWindow, &windowHeight, &windowWidth);
	
	m_programId = glCreateProgram();
	loadShaders(MODEL_VSHADER, MODEL_FSHADER);
	
	m_parser = new ObjParser(baseDir, modelFile);
	std::vector<ObjParser::Geometry*>* geometryList = m_parser->getGeometry();
	
	glBindAttribLocation(m_programId, TDMODEL_ATTRIB_IN_POSITION_ID, "in_Position");
	glBindAttribLocation(m_programId, TDMODEL_ATTRIB_IN_NORMAL_ID, "in_Normals");
	glBindAttribLocation(m_programId, TDMODEL_ATTRIB_IN_TEXCOORD_ID, "in_TexCoord");
	glBindFragDataLocation(m_programId, 0, "out_Color");
	glLinkProgram(m_programId);
	glUseProgram(m_programId);
	
	size_t geometryListSize = geometryList->size();
	
	m_vao = (GLuint*)malloc(geometryListSize*sizeof(GLuint));
	m_VBOVertices = (GLuint*)malloc(geometryListSize*sizeof(GLuint));
	m_VBONormals = (GLuint*)malloc(geometryListSize*sizeof(GLuint));
	m_VBOTextureCoords = (GLuint*)malloc(geometryListSize*sizeof(GLuint));
	m_textureObject = (GLuint*)malloc(geometryListSize*sizeof(GLuint));
	
	glGenVertexArrays(geometryListSize, m_vao);
	glGenBuffers(geometryListSize, m_VBOVertices);
	glGenBuffers(geometryListSize, m_VBONormals);
	glGenBuffers(geometryListSize, m_VBOTextureCoords);
	glGenTextures(geometryListSize, m_textureObject);
	
	for (int i = 0; i < geometryListSize; i++) {
		glBindVertexArray(m_vao[i]);
		ObjParser::Geometry* geometry = geometryList->at(i);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * geometry->numVertices, &(geometry->vertices[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(TDMODEL_ATTRIB_IN_POSITION_ID, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TDMODEL_ATTRIB_IN_POSITION_ID);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBONormals[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry->numVertices, &(geometry->normals[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(TDMODEL_ATTRIB_IN_NORMAL_ID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TDMODEL_ATTRIB_IN_NORMAL_ID);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextureCoords[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * geometry->numVertices, &(geometry->textureCoords[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(TDMODEL_ATTRIB_IN_TEXCOORD_ID, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TDMODEL_ATTRIB_IN_TEXCOORD_ID);
		
		glUniform4fv(glGetUniformLocation(m_programId, "uAmbientProduct"), 1, glm::value_ptr(geometry->Ka));
		glUniform4fv(glGetUniformLocation(m_programId, "uDiffuseProduct"), 1, glm::value_ptr(geometry->Kd));
		glUniform4fv(glGetUniformLocation(m_programId, "uSpecularProduct"), 1, glm::value_ptr(geometry->Ks));
		glUniform1fv(glGetUniformLocation(m_programId, "uSpecularHighlight"), 1, &(geometry->Ns));
		
		glBindTexture(GL_TEXTURE_2D, m_textureObject[i]);
		// TODO: Use multiple textures per geometry?
		char* textureFilename = (char*)malloc(sizeof(char) * (strlen(baseDir) + 4096));
		strcpy(textureFilename, baseDir);
		strcat(textureFilename, geometry->map_Kd); // TODO: Don't hard code Kd
		
		SDL_Surface* textureImage = loadTexture(textureFilename);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureImage->pixels);
		
		glUniform1i(glGetUniformLocation(m_programId, "uTexture"), 0);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		free(textureFilename);
		
		m_model = glm::mat4(1.0f);
		m_view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 10.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		m_proj = glm::perspective(0.785f, (float)windowHeight/(float)windowWidth, 0.1f, 100.0f);
		
		glUniformMatrix4fv(glGetUniformLocation(m_programId, UNIFORM_MODEL), 1, GL_FALSE, glm::value_ptr(m_model));
		glUniformMatrix4fv(glGetUniformLocation(m_programId, UNIFORM_VIEW), 1, GL_FALSE, glm::value_ptr(m_view));
		glUniformMatrix4fv(glGetUniformLocation(m_programId, UNIFORM_PROJ), 1, GL_FALSE, glm::value_ptr(m_proj));
	}
}

ThreeDModel::~ThreeDModel() {

}

void ThreeDModel::draw() {
	std::vector<ObjParser::Geometry*>* geometryList = m_parser->getGeometry();
	for (int i = 0; i < geometryList->size(); i++) {
		glBindVertexArray(m_vao[i]);
		glUseProgram(m_programId);
		glBindTexture(GL_TEXTURE_2D, m_textureObject[i]);
		glDrawArrays(GL_TRIANGLES, 0, geometryList->at(i)->numVertices);
	}
}
