#include "ObjParser.h"

ObjParser::ObjParser(const char* baseDir, const char* objFilename) {
	m_baseDir = (char*)malloc(sizeof(char) * (strlen(baseDir) + 1));
	strcpy(m_baseDir, baseDir);
	m_objFilename = (char*)malloc(sizeof(char) * (strlen(m_baseDir) + strlen(objFilename) + 1));
	strcpy(m_objFilename, m_baseDir);
	strcat(m_objFilename, objFilename);
	
	parseObj();
	parseMtl();
}

ObjParser::~ObjParser() {
	free(m_baseDir);
	free(m_objFilename);
	free(m_mtlFilename);
	m_geometryList.clear();
	m_materialMappings.clear();
}

void ObjParser::parseObj() {
	FILE* obj;
	obj = fopen(m_objFilename, "r");
	if (obj == NULL) {
		fprintf(stderr, "Failed to open file: %s\n", m_objFilename);
		return;
	}
	
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	
	char* line = (char*)malloc(sizeof(char) * MAXLINESIZE);
	char* mtl = (char*)malloc(sizeof(char) * MAXLINESIZE);
	char* material = (char*)malloc(sizeof(char) * MAXLINESIZE);
	bool hasVertices, hasNormals, hasTextureCoords = false;
	float fl[3];
	int vertexIndices[3] = {0, 0, 0};
	int normalIndices[3] = {0, 0, 0};
	int textureCoordIndices[3] = {0, 0, 0};
	glm::vec4 com = glm::vec4(0.0, 0.0, 0.0, 0.0); // Model's center of mass
	
	while (true) {
		fgets(line, MAXLINESIZE, obj);
		if (feof(obj))
			break;
		
		if (sscanf(line, "mtllib %s", mtl)) { // material library
			m_mtlFilename = (char*)malloc(sizeof(char) * (strlen(m_baseDir) + strlen(mtl) + 1));
			strcpy(m_mtlFilename, m_baseDir);
			strcat(m_mtlFilename, mtl);
		} else if (sscanf(line, "usemtl %s", material)) { // material reference
			Geometry* g = new Geometry();
			char* matName = (char*)malloc((strlen(material)+1) * sizeof(char));
			strcpy(matName, material);
			m_geometryList.push_back(g);
			
			std::map<char*,std::vector<Geometry*>*>::iterator iter = m_materialMappings.find(material);
			if (iter == m_materialMappings.end()) {
				std::vector<Geometry*>* vec = new std::vector<Geometry*>;
				vec->push_back(g);
				m_materialMappings.insert(std::pair<char*,std::vector<Geometry*>*>(matName, vec));
			} else {
				iter->second->push_back(g);
			}
		} else if (sscanf(line, "v %f %f %f", &fl[0], &fl[1], &fl[2]) == 3) { // Vertices
			vertices.push_back(glm::vec4(fl[0], fl[1], fl[2], 1.0));
			com += glm::vec4(fl[0], fl[1], fl[2], 0.0);
		} else if (sscanf(line, "vn %f %f %f", &fl[0], &fl[1], &fl[2]) == 3) { // Normals
			normals.push_back(glm::vec3(fl[0], fl[1], fl[2]));
		} else if (sscanf(line, "vt %f %f", &fl[0], &fl[1]) == 2) { // Texture coordinates
			textureCoords.push_back(glm::vec2(fl[0], fl[1]));
		} else {
			if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", 
					&vertexIndices[0], &textureCoordIndices[0], &normalIndices[0], 
					&vertexIndices[1], &textureCoordIndices[1], &normalIndices[1], 
					&vertexIndices[2], &textureCoordIndices[2], &normalIndices[2]) == 9) {
				hasVertices = hasTextureCoords = hasNormals = true;
			} else if (sscanf(line, "f %d//%d %d//%d %d//%d", 
					&vertexIndices[0], &normalIndices[0], 
					&vertexIndices[1], &normalIndices[1], 
					&vertexIndices[2], &normalIndices[2]) == 6) {
				hasVertices = hasNormals = true;
			} else if (sscanf(line, "f %d/%d %d/%d %d/%d", 
					&vertexIndices[0], &textureCoordIndices[0], 
					&vertexIndices[1], &textureCoordIndices[1], 
					&vertexIndices[2], &textureCoordIndices[2]) == 6) {
				hasVertices = hasTextureCoords = true;
			} else if (sscanf(line, "f %d %d %d", 
					&vertexIndices[0], &vertexIndices[1], &vertexIndices[2]) == 3) {
				hasVertices = true;
			} else {
				continue;
			}

			for (int w = 0; w < 3; w++) {
				if (hasVertices) {
					int idx = vertexIndices[w] < 0 ? vertices.size() + vertexIndices[w] : vertexIndices[w] - 1;
					
					m_geometryList.back()->vertices.push_back(vertices[idx]);
					m_geometryList.back()->numVertices++;
				}
				if (hasNormals) {
					int idx = normalIndices[w] < 0 ? vertices.size() + normalIndices[w] : normalIndices[w] - 1;
					
					m_geometryList.back()->normals.push_back(normals[idx]);
				}
				if (hasTextureCoords) {
					int idx = textureCoordIndices[w] < 0 ? vertices.size() + textureCoordIndices[w] : textureCoordIndices[w] - 1;
					
					m_geometryList.back()->textureCoords.push_back(textureCoords[idx]);
				}
			}
		}
	}
	
	//vertices.clear();
	//normals.clear();
	//textureCoords.clear();
	
	free(line);
	free(mtl);
	free(material);
	fclose(obj);
}

void ObjParser::parseMtl() {
	FILE* mtl;
	mtl = fopen(m_mtlFilename, "r");
	if (mtl == NULL) {
		fprintf(stderr, "Failed to open file: %s\n", m_mtlFilename);
		return;
	}
	
	std::vector<Geometry*>* currentGeometryList;
	char line[MAXLINESIZE];
	char value[MAXLINESIZE];
	float fl[3];
	
	while (true) {
		fgets(line, MAXLINESIZE, mtl);
		if (feof(mtl)) {
			break;
		}
		
		if (sscanf(line, "newmtl %s", value)) { // material reference
			char* mat = (char*)malloc(sizeof(char) * strlen(value) + sizeof(char));
			strcpy(mat, value);
			currentGeometryList = m_materialMappings.find(value)->second;
		} else if (sscanf(line, "map_Ka %s", value)) { // ambient texture map
			char* img = (char*)malloc(sizeof(char) * strlen(value) + sizeof(char));
			strcpy(img, value);
			
			for (std::vector<Geometry*>::iterator iter = currentGeometryList->begin(); iter != currentGeometryList->end(); iter++)
				(*iter)->map_Ka = img;
		} else if (sscanf(line, "map_Kd %s", value)) { // diffuse texture map
			char* img = (char*)malloc(sizeof(char) * strlen(value) + sizeof(char));
			strcpy(img, value);
			
			for (std::vector<Geometry*>::iterator iter = currentGeometryList->begin(); iter != currentGeometryList->end(); iter++)
				(*iter)->map_Kd = img;
		} else if (sscanf(line, "map_Ks %s", value)) { // specular color texture map
			char* img = (char*)malloc(sizeof(char) * strlen(value) + sizeof(char));
			strcpy(img, value);
			
			for (std::vector<Geometry*>::iterator iter = currentGeometryList->begin(); iter != currentGeometryList->end(); iter++)
				(*iter)->map_Ks = img;
		} else if (sscanf(line, "map_Ns %s", value)) { // specular highlight component
			char* img = (char*)malloc(sizeof(char) * strlen(value) + sizeof(char));
			strcpy(img, value);
			
			for (std::vector<Geometry*>::iterator iter = currentGeometryList->begin(); iter != currentGeometryList->end(); iter++)
				(*iter)->map_Ns = img;
		} else if (sscanf(line, "Ka %f %f %f", &fl[0], &fl[1], &fl[2]) == 3) { // ambient coefficient
			for (std::vector<Geometry*>::iterator iter = currentGeometryList->begin(); iter != currentGeometryList->end(); iter++)
				(*iter)->Ka = glm::vec3(fl[0], fl[1], fl[2]);
		} else if (sscanf(line, "Ks %f %f %f", &fl[0], &fl[1], &fl[2]) == 3) { // specular coefficient
			for (std::vector<Geometry*>::iterator iter = currentGeometryList->begin(); iter != currentGeometryList->end(); iter++)
				(*iter)->Ks = glm::vec3(fl[0], fl[1], fl[2]);
		} else if (sscanf(line, "Kd %f %f %f", &fl[0], &fl[1], &fl[2]) == 3) { // diffuse coefficient
			for (std::vector<Geometry*>::iterator iter = currentGeometryList->begin(); iter != currentGeometryList->end(); iter++)
				(*iter)->Kd = glm::vec3(fl[0], fl[1], fl[2]);
		} else if (sscanf(line, "Ns %f", &fl[0])) { // Shininess
			for (std::vector<Geometry*>::iterator iter = currentGeometryList->begin(); iter != currentGeometryList->end(); iter++)
				(*iter)->Ns = fl[0];
		}
	}
	
	fclose(mtl);
}

std::vector<ObjParser::Geometry*>* ObjParser::getGeometry() {
	return &m_geometryList;
}
