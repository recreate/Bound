#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <glm/glm.hpp>

#include "DrawableEntity.h"

class Screen : public DrawableEntity {
public:
	Screen();
	virtual ~Screen();
	
	virtual void draw();
private:
	glm::vec4* SCREEN_VERTICES;
};

#endif // _SCREEN_H_
