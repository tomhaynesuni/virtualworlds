#ifndef CSKYBOX_H
#define CSKYBOX_H
#include "core.h"


using namespace glm;

class cSkybox
{
public:
	cSkybox();
	~cSkybox();
	void init();
	void update(class cScene* pScene);
	 
	
	char** m_tex;
	vec3* map_directions = new vec3[6];

};
#endif