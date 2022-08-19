#include "cSkybox.h"
#include "core.h"
#include "cScene.h"
//#include "cTexture.h"


//////////////////////////////////////////////////////////////////////////////////////////
// cSkybox() - constructor
//////////////////////////////////////////////////////////////////////////////////////////
cSkybox::cSkybox()
{
	m_tex = new char* [6];
	m_tex[0] = (char*)("right.tga");
	m_tex[1] = (char*)("left.tga");
	m_tex[2] = (char*)("top.tga");
	m_tex[3] = (char*)("base.tga");
	m_tex[4] = (char*)("front.tga");
	m_tex[5] = (char*)("back.tga");

	map_directions[0] = vec3(10.0f, 0.0f, 0.0f);
	map_directions[1] = vec3(-10.0f, 0.0f, 0.0f);
	map_directions[2] = vec3(0.0f, 10.0f, 0.0f);
	map_directions[3] = vec3(0.0f, -10.0f, 0.0f);
	map_directions[4] = vec3(0.0f, 0.0f, -10.0f);
	map_directions[5] = vec3(0.0f, 0.0f, 10.0f);
}


//////////////////////////////////////////////////////////////////////////////////////////
// ~cSkybox() - destructor
//////////////////////////////////////////////////////////////////////////////////////////
cSkybox::~cSkybox()
{
	if (m_tex)
	{
		for (int i = 0; i < 6; i++)
		{
			delete[] m_tex[i];
			m_tex[i] = NULL;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
// init() - 
//////////////////////////////////////////////////////////////////////////////////////////
void cSkybox::init()
{
	// load in all textures for this environment map here..
	for (int i = 0; i < 6; i++) {
		cTex.loadCubeMapTGA(m_tex[i], i);
	}
	
}

void cSkybox::update(class cScene* pScene)
{
	//pointer to the camera object
	cCamera* pCamera = &pScene->m_Camera[pScene->m_cameraId];

	//store camera start position
	vec3 camera_start_pos = pCamera->m_pos;
	vec3 camera_start_dir = pCamera->m_dir;
	float camera_start_fov = pCamera->m_fov;

	//move camera to mesh[0] position
	pCamera->m_pos = pScene->m_Mesh[0].m_transform.m_pos;

	//set the fov to 90 degrees
	pCamera->m_fov = 90.0f;
	pCamera->init();

	// loop through each view of the camera and recalc the cube map
	for (int i = 0; i < 6; i++)
	{
		// set LookAt matrix to point camera towards the origin
		pCamera->lookAt(pCamera->m_pos, map_directions[i]);

		// render the scene
		// this can cause an infinte loop with render and update
		pScene->render(1);

		// grab a copy of what we lhave just rendered from the back buffer
		glReadBuffer(GL_BACK);

		// then converts this to a texture
		glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 0, 0, 1024, 1024, 0);

		// continue drawing to the back buffer
		glDrawBuffer(GL_BACK);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	// reset the camera to it's start position
	pCamera->m_fov = camera_start_fov;
	
	// reset fov
	pCamera->lookAt(camera_start_pos, camera_start_dir);
	pCamera->init();

}


