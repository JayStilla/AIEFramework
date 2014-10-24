#pragma once

#include "Application.h"
#include <stb_image.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

// derived application class that wraps up all globals neatly
class TessellationTut : public Application
{
public:

	TessellationTut();
	virtual ~TessellationTut();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	//Custom Code
	unsigned int m_vao; 
	unsigned int m_vbo; 
	unsigned int m_ibo; 
	unsigned int m_shader; 

	GLuint m_texture; 
	GLuint m_displacement; 
};