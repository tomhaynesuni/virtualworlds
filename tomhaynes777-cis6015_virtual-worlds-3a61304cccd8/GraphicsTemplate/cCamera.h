#pragma once
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

class cCamera
{
public:
	cCamera();
	~cCamera();

	void init();
	void update();
	void lookAt(const vec3 pos_, const vec3 dir_);

	glm::mat4 projectionMatrix;		// projection matrix
	glm::mat4 viewMatrix;			// view matrix

	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_dir; 



	float m_fov;
	float m_near;
	float m_far;
};

