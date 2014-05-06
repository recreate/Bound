#ifndef _MENUITEM_H_
#define _MENUITEM_H_

#include <glm/glm.hpp>

#include "DrawableEntity.h"

class MenuItem : public DrawableEntity {
public:
	MenuItem();
	virtual ~MenuItem();
	
	virtual void draw();
	virtual void action();
	
	virtual glm::vec2 getPosition();
	virtual float getWidth();
	virtual float getHeight();
	
protected:

};

#endif // _MENUITEM_H_