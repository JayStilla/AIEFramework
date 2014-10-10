#pragma once

#include "Application.h"
#include "ParticleSystem.h"
#include <glm/glm.hpp>

// derived application class that wraps up all globals neatly
class ParticleTutorial : public Application
{
public:

	ParticleTutorial();
	virtual ~ParticleTutorial();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	void CreateShaders();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	//Custom Code

	//Buffers
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	//Shaders
	unsigned int m_programID;
	unsigned int m_shader;
	unsigned int m_vertShader;
	unsigned int m_fragShader;

	ParticleSystem *m_emitter; 
};