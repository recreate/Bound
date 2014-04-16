#ifndef _OBJPARSER_H_
#define _OBJPARSER_H_

#include <stdio.h>
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include "glew.h"

#define MAXLINESIZE 4096

class ObjParser {
public:
	ObjParser(const char* baseDir, const char* objFilename);
	~ObjParser();
	
	struct Geometry {
		unsigned int numVertices;
		
		std::vector<glm::vec4> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureCoords;
		
		glm::vec3 Ka;
		glm::vec3 Kd;
		glm::vec3 Ks;
		float Ns;

		char* map_Ka;
		char* map_Kd;
		char* map_Ks;
		char* map_Ns;
	};
	
	std::vector<Geometry*>* getGeometry();
	
private:
	struct cmp_str {
		bool operator()(const char* a, const char* b) {
			return strcmp(a, b) < 0;
		}
	};
	
	char* m_baseDir;
	char* m_objFilename;
	char* m_mtlFilename;
	
	void parseObj();
	void parseMtl();
	std::vector<Geometry*> m_geometryList;
	std::map<char*, std::vector<Geometry*>*, cmp_str> m_materialMappings;
};

#endif // _OBJPARSER_H_