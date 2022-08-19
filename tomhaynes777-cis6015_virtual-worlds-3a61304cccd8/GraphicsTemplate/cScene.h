#pragma once

#include "core.h"

class cMesh;
class cSkybox;


class cScene
{
public:

	cScene() 
	{
		m_cameraId	= 0;
		m_lightId	= 0;
		m_Camera	= NULL;
		m_Light		= NULL;
		m_Mesh		= NULL;
		m_Skybox	= NULL;
		width		= 0;
		height		= 0;
	}

	~cScene() 
	{
		if (m_tex != nullptr) {
			
			delete m_tex;
			m_tex = nullptr;
		}
	}
	void init();
	void render(const int invisMesh_);
	void update();
	void openSDF();

	cShaderInfo		m_ShaderInfo;
	cCamera*		m_Camera;
	cLight*			m_Light;
	cMesh*			m_Mesh;
	cSkybox*		m_Skybox;

	sShaderDetails* ShaderTable;

	GLuint* m_tex;

	int m_shader_count;
	int m_camera_count;
	int m_light_count;
	int m_mesh_count;
	int m_cameraId;
	int m_lightId;
	GLsizei width;
	GLsizei height;

private:

};