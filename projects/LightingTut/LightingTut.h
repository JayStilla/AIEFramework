#pragma once

#include "Application.h"
#include <glm/glm.hpp>
#include <FBXFile.h>

struct DirectionalLight
{
	glm::vec3 AmbientLight; 
	glm::vec3 LightDirection; 
	glm::vec3 LightColour; 
	glm::vec3 LightSpecular; 
};

// derived application class that wraps up all globals neatly
class LightingTut : public Application
{
public:

	LightingTut();
	virtual ~LightingTut();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	//Custom Code
	void createOpenGLBuffers(FBXFile* a_fbx);
	void cleanupOpenGLBuffers(FBXFile* a_fbx);

	unsigned int m_vertShader; 
	unsigned int m_fragShader; 
	unsigned int m_shader; 

	FBXFile *m_fbx;

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	
};
