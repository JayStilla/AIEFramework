#pragma once

#include "Application.h"
#include <glm/glm.hpp>
#include "Tutorial6.h"


// derived application class that wraps up all globals neatly
class GPUParticleSystem : public Application
{
public:

	GPUParticleSystem();
	virtual ~GPUParticleSystem();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	Tutorial6* m_emitter; 

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;


};