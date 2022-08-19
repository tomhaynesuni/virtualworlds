#include "cCamera.h"


/////////////////////////////////////////////////////////////////////////////////////
// constructor
/////////////////////////////////////////////////////////////////////////////////////
cCamera::cCamera()
{
	m_fov = 45.0f;
	m_near = 0.1f;
	m_far = 100.0f;

	m_pos = vec3(0.0f, 0.0f, 7.5);
	m_rot - vec3(0.0f, 0.0f, 0.0f);
	m_dir = vec3(0.0f, 0.0f, -1.0f);

	projectionMatrix = glm::perspective(glm::radians(m_fov), (float)800.0f / (float)600.0f, m_near, m_far);
	viewMatrix = mat4(1.0f);
}

/////////////////////////////////////////////////////////////////////////////////////
// destructor
/////////////////////////////////////////////////////////////////////////////////////
cCamera::~cCamera()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// init() - 
/////////////////////////////////////////////////////////////////////////////////////
void cCamera::init()
{
	projectionMatrix = glm::perspective(glm::radians(m_fov), (float)800.0f / (float)600.0f, m_near, m_far);
}

//GL_TEXTURE_CUBE_MAP_POSITIVE_X	// ADDED FROM VIDEO
//GL_TEXTURE_CUBE_MAP_NEGATVE_X
//GL_TEXTURE_CUBE_MAP_POSITIVE_Y
//GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
//GL_TEXTURE_CUBE_MAP_POSITIVE_Z
//GL_TEXTURE_CUBE_MAP_NEGATIVE_Z

//vec3 directions[6] = {			// ADDED FROM VIDEO
//	vec3(1.0, 0.0, 0.0), // left
//	vec3(-1.0, 0.0, 0.0), // right
//	vec3(0.0, 1.0, 0.0),
//	vec3(0.0, -1.0, 0.0),
//};




/////////////////////////////////////////////////////////////////////////////////////
// update() - 
/////////////////////////////////////////////////////////////////////////////////////
void cCamera::update()
{	
	/*mat4 r	= glm::rotate(mat4(1.0f), glm::radians(-m_rot.z), vec3(0.0f, 0.0f, 1.0f));
	r		= glm::rotate(r, glm::radians(-m_rot.y), vec3(0.0f, 1.0f, 0.0f));
	r		= glm::rotate(r, glm::radians(-m_rot.x), vec3(1.0f, 0.0f, 0.0f));
	mat4 t	= glm::translate(mat4(1.0f), vec3(-m_pos));

	viewMatrix = r * t;*/

	lookAt(m_pos, m_dir);
}

void cCamera::lookAt(const vec3 pos_, const vec3 dir_)
{
	m_pos = pos_;
	m_dir = dir_;
	m_dir = normalize(m_dir);
	vec3 upVector = vec3(0.0f);

	if (m_dir == vec3(0.0f, 1.0f, 0.0f)) {
		upVector = vec3(0.0f, 0.0f, 1.0f);
	}
	else if (m_dir == vec3(0.0f, -1.0f, 0.0f)) {
		upVector = vec3(0.0f, 0.0f, -1.0f);
	}
	else
		upVector = vec3(0.0f, 1.0f, 0.0f);
	//viewMatrix = glm::lookAt(cameraPos, directions[0], upVector);		// ADDED FROM VIDEO

	viewMatrix = glm::lookAt(m_pos, m_pos + m_dir, upVector);
}
