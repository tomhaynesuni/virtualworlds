#include "core.h"

/////////////////////////////////////////////////////////////////////////////////////
// update() - 
/////////////////////////////////////////////////////////////////////////////////////
void cScene::update()
{
	m_Camera[m_cameraId].update();

	for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].m_transform.update();
	}

	m_Skybox->update(this);
	
}
/////////////////////////////////////////////////////////////////////////////////////
// init() - 
/////////////////////////////////////////////////////////////////////////////////////
void cScene::init()
{
	m_tex = new GLuint [1];
	m_tex = { 0 };

	openSDF();

	if(m_Skybox)
		m_Skybox->init();

	for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].init();
	}

	for (int i = 0; i < m_camera_count; i++)
	{
		m_Camera[i].init();
	}

	glBindVertexArray(0);

	m_ShaderInfo.create();
}

/////////////////////////////////////////////////////////////////////////////////////
// render() - 
/////////////////////////////////////////////////////////////////////////////////////
void cScene::render(const int invisMesh_)
{
	// because update is called in render - skybox update can infinite loop (if skybox.update is in scene.update as you would expect)
	//update();
	
	// not being called for now 
	/*if(invisMesh_)
	m_Skybox->update(this); */

	int invisMesh = 0;
	if (invisMesh_) {
		invisMesh = invisMesh_ - 1;
	}
	
	for (int i = 0; i < m_mesh_count; i++)
	{
		if (invisMesh_ == 0) {
			m_Mesh[i].render(this, &m_ShaderInfo);
		}
		else if (i != invisMesh) {
			m_Mesh[i].render(this, &m_ShaderInfo);
		}
	}

		m_Mesh[0].render(this, &m_ShaderInfo);
	//update();

	// Multipass render plane
	glActiveTexture(GL_TEXTURE0 + (GLuint)(m_Mesh[3].m_tex[0]));
	glReadBuffer(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, (GLuint)(m_Mesh[3].m_tex[0]));
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 800, 600, 0);

	glBindTexture(GL_TEXTURE_2D, (GLuint)(m_Mesh[3].m_tex[0]));
	glDrawBuffer(GL_BACK);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//glActiveTexture(GL_TEXTURE0 + 3);

	m_Mesh[3].render(this, &m_ShaderInfo);


	// store the camera settings - i.e. pos, oritentation					// second attempt at skybox rendering, based on class tutorial recording
	//vec3 camera_start_pos = m_Camera->m_pos;
	//vec3 camera_start_dir = m_Camera->m_dir;
	//float camera_start_fov = m_Camera->m_fov;

	//for (int pass = 0; pass < 6; pass++)						
	//{
	////	// six render passes

	////	// each pass position camera at player pos
	////	// rotate camera using glm::LookAt( cameraPos, direction, upVector
	//	m_Camera->m_fov = 90.0f;
	//	m_Camera->init();
	//	m_Camera->lookAt(m_Camera->m_pos, m_Skybox->map_directions[pass]);

	//	// render the scene - do not render the player object
	

	// grab back buffer
	//	glReadBuffer(GL_BACK);
	//	glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + pass, 0, GL_RGBA, 0, 0, 1024, 1024, 0);
	//	//glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)(m_Mesh[0].m_tex));

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////	// convert to cube map texture															// first attempt at skybox rendering
	//	//glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + pass, 0, GL_RGBA, 0, 0, 1024, 1024, 0);
	//	glDrawBuffer(GL_BACK);

	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//	
	//}
	//
	//// restore camera back to original settings - i.e. position, orientation
	//m_Camera->m_fov = camera_start_fov;
	//m_Camera->lookAt(camera_start_pos, camera_start_dir);
	//m_Camera->init();
	
	// render the entire scene using the new cube map
	/*for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].render(this, &m_ShaderInfo);
	}*/
	/////////////////////////////////////////////////////////////////////////////////////

	


	//Dynamic cube map / global reflection
	
	//Store the camera’s current settings
	/*vec3 camPos = m_Camera->m_pos;
	vec3 camDir = m_Camera->m_dir;*/

	////Move the camera to the centre of the player mesh. 
	////Rotate the camera and render the scene from each of the six viewpoints needed to create the cube map. 
	//glActiveTexture(GL_TEXTURE0 + (GLuint)(m_Mesh[0].m_tex[0]));
	//glReadBuffer(GL_BACK);
	//
	////RIGHT
	//vec3 rOffset = vec3(10.0f, 0.0f, 0.0f);
	//m_Camera->lookAt(m_Mesh[0].m_transform.m_pos, vec3(camPos + rOffset));

	//glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)(m_Mesh[0].m_tex[0]));
	//glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, 0, 0, 800, 600, 0);
	//glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_ARRAY_BUFFER, GL_TEXTURE_CUBE_MAP_POSITIVE_X, (GLuint)(m_Mesh[0].m_tex[0]), 0);
	//
	////LEFT
	//vec3 lOffset = vec3(-10.0f, 0.0f, 0.0f);
	//m_Camera->lookAt(m_Mesh[0].m_transform.m_pos, vec3(camPos + lOffset));
	//
	//glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)(m_Mesh[0].m_tex[0]));
	//glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, 0, 0, 800, 600, 0);
	//glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_ARRAY_BUFFER, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, (GLuint)(m_Mesh[0].m_tex[0]), 0);

	////UP
	//vec3 uOffset = vec3(0.0f, 10.0f, 0.0f);
	//m_Camera->lookAt(m_Mesh[0].m_transform.m_pos, vec3(camPos + uOffset));

	//glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)(m_Mesh[0].m_tex[0]));
	//glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, 0, 0, 800, 600, 0);
	//glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_ARRAY_BUFFER, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, (GLuint)(m_Mesh[0].m_tex[0]), 0);

	////DOWN
	//vec3 dOffset = vec3(0.0f, -10.0f, 0.0f);
	//m_Camera->lookAt(m_Mesh[0].m_transform.m_pos, vec3(camPos + dOffset));

	//glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)(m_Mesh[0].m_tex[0]));
	//glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, 0, 0, 800, 600, 0);
	//glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_ARRAY_BUFFER, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, (GLuint)(m_Mesh[0].m_tex[0]), 0);

	////BACK
	//vec3 bOffset = vec3(0.0f, 0.0f, 10.0f);
	//m_Camera->lookAt(m_Mesh[0].m_transform.m_pos, vec3(camPos + bOffset));

	//glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)(m_Mesh[0].m_tex[0]));
	//glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, 0, 0, 800, 600, 0);
	//glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_ARRAY_BUFFER, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, (GLuint)(m_Mesh[0].m_tex[0]), 0);

	////FRONT
	//vec3 fOffset = vec3(0.0f, 0.0f, -10.0f);
	//m_Camera->lookAt(m_Mesh[0].m_transform.m_pos, vec3(camPos + fOffset));

	//glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)(m_Mesh[0].m_tex[0]));
	//glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, 0, 0, 800, 600, 0);
	//glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_ARRAY_BUFFER, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, (GLuint)(m_Mesh[0].m_tex[0]), 0);


	 
	//After each render, grab the contents of the BACK bufferand store the image in the cube map.
	 
	//Restore the camera back to its’ original settings
	//m_Camera->lookAt(camPos, camDir);
	 
	//Pass the newly created cube map to your shaderand render the scene.


}

/////////////////////////////////////////////////////////////////////////////////////
// openSDF() - Opens up a scene descriptor file
/////////////////////////////////////////////////////////////////////////////////////
void cScene::openSDF()
{
	// load the scene file here

	FILE* fp = NULL;
	
	fopen_s(&fp, "scene.sdf", "r");

	if (!fp)
		assert(0);

	char buffer[256] = { "\0"};
	float value;
	
	////////////////////////////////////////////////////////////
	// CAMERA
	////////////////////////////////////////////////////////////
	fscanf_s(fp, "%s%d", buffer, 256, &m_camera_count);		// LIGHT_COUNT: 2

	m_Camera = new cCamera[m_camera_count];

	for (int i = 0; i < m_camera_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, buffer, 256); // CAMERA {
		fscanf_s(fp, "%s%f", buffer, 256, &m_Camera[i].m_fov);		// FOV:	45.0
		fscanf_s(fp, "%s%f", buffer, 256, &m_Camera[i].m_near);		// NEAR:	0.5
		fscanf_s(fp, "%s%f", buffer, 256, &m_Camera[i].m_far);		// FAR:	100.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Camera[i].m_pos.x, &m_Camera[i].m_pos.y, &m_Camera[i].m_pos.z);		// POS:		0.0 0.0 -5.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Camera[i].m_rot.x, &m_Camera[i].m_rot.y, &m_Camera[i].m_rot.z);		// ROT:	0.0 0.0 0.0
		fscanf_s(fp, "%s", buffer, 256);				// }
	}


	////////////////////////////////////////////////////////////
	// LIGHTS
	////////////////////////////////////////////////////////////
	
	fscanf_s(fp, "%s%d", buffer, 256, &m_light_count);		// LIGHT_COUNT: 2

	// allocate block of memory to store the lights..
	m_Light = new cLight[m_light_count];

	for (int i = 0; i < m_light_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, buffer, 256);	// LIGHT: }
		fscanf_s(fp, "%s%d", buffer, 256, &m_Light[i].m_type); // TYPE:	0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Light[i].m_pos.x, &m_Light[i].m_pos.y, &m_Light[i].m_pos.z); // POS:	-25.0 0.0 20.0
		fscanf_s(fp, "%s", buffer, 256);				// }
	}

	////////////////////////////////////////////////////////////
	// SKYBOX
	////////////////////////////////////////////////////////////
	int count = 0;

	fscanf_s(fp, "%s%d", buffer, 256, &count);		// ENVIRONMENT_MAP: 1
	fscanf_s(fp, "%s", buffer, 256);				// {

	// check if we are trying to load a skybox
	if ( count )
	{
		// allocate block of memory to store the 6 x textures needed for the skybox
		m_Skybox = new cSkybox[1];
		m_Skybox->m_tex = (char**)malloc(6 * sizeof(char*));
		char path[64];
		for (int i = 0; i < 6; i++)
		{
			strcpy_s(path, "tga/");
			// load all six texture paths
			fscanf_s(fp, "%s%s", buffer, 256, buffer, 256);
			strcat_s(path, buffer);
			int sz = strlen(path) + 1;
			m_Skybox->m_tex[i] = (char*)malloc(sz * sizeof(char));
			strcpy_s(m_Skybox->m_tex[i], sizeof(char) * sz, path);
		}
	}

	fscanf_s(fp, "%s", buffer, 256);				// }



	////////////////////////////////////////////////////////////
	// MESHES
	////////////////////////////////////////////////////////////
	char filename[256];
	char name[256];

	fscanf_s(fp, "%s%d", buffer, 256, &m_mesh_count);		// MESH_COUNT: 4


	// allocate block of memory to store the mesh objects..
	m_Mesh = new cMesh[m_mesh_count];

	for (int i = 0; i < m_mesh_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, m_Mesh[i].m_filename, 256);	//MESH: .obj
		fscanf_s(fp, "%s", buffer, 256);					// }
		fscanf_s(fp, "%s%s", buffer, 256, m_Mesh[i].m_name, 256);		//MESH: name
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_pos.x, &m_Mesh[i].m_transform.m_pos.y, &m_Mesh[i].m_transform.m_pos.z);					// POS:	0.0 0.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_rot.x, &m_Mesh[i].m_transform.m_rot.y, &m_Mesh[i].m_transform.m_rot.z);					// ROT : 2.0 2.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_rot_incr.x, &m_Mesh[i].m_transform.m_rot_incr.y, &m_Mesh[i].m_transform.m_rot_incr.z);	// ROT_INCR:	1.0 1.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_scale.x, &m_Mesh[i].m_transform.m_scale.y, &m_Mesh[i].m_transform.m_scale.z);			// SCALE : 1.25 1.25 1.25
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_vel.x, &m_Mesh[i].m_transform.m_vel.y, &m_Mesh[i].m_transform.m_vel.z);					// VEL : 0.2 0.1 0.0
		fscanf_s(fp, "%s%d", buffer, 256, &m_Mesh[i].m_shaderID); // SHADER_ID	0

		fscanf_s(fp, "%s", buffer, 256);					// }
	}

	////////////////////////////////////////////////////////////
	// SHADERS
	////////////////////////////////////////////////////////////
	fscanf_s(fp, "%s%d", buffer, 256, &m_shader_count);		// SHADER_COUNT: 2

	ShaderTable = new sShaderDetails[m_shader_count];
	
	fscanf_s(fp, "%s", buffer, 256); // SHADER:

	for (int i = 0; i < m_shader_count; i++)
	{
		// init shader types..
		for( int j=0; j<6; j++ )
			ShaderTable[i].types[j] = 0;


		fscanf_s(fp, "%s", buffer, 256);		
		strcpy_s(ShaderTable[i].filename, buffer);
		
		int loop_count = 0;
		
		while (strcmp(buffer, "SHADER:") != 0)
		{
			loop_count++;

			fscanf_s(fp, "%s", buffer, 256);
			if (strcmp(buffer, "SHADER:") == 0)
				break;

			// sort the shader by type and add to list..
			if (strcmp(buffer, "VERT_SHDR") == 0)
				ShaderTable[i].types[0] = GL_VERTEX_SHADER;
			else
			if (strcmp(buffer, "CTRL_SHDR") == 0)
				ShaderTable[i].types[1] = GL_TESS_CONTROL_SHADER;
			else
			if (strcmp(buffer, "EVAL_SHDR") == 0)
				ShaderTable[i].types[2] = GL_TESS_EVALUATION_SHADER;
			else
			if (strcmp(buffer, "GEOM_SHDR") == 0)
				ShaderTable[i].types[3] = GL_GEOMETRY_SHADER;
			else
			if (strcmp(buffer, "FRAG_SHDR") == 0)
				ShaderTable[i].types[4] = GL_FRAGMENT_SHADER;
			else
				ShaderTable[i].types[5] = GL_COMPUTE_SHADER;

			if (loop_count == 6)
				break;
		};
	}

	fclose(fp);

}