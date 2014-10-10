#pragma once

#include "Application.h"
#include <glm/glm.hpp>
#include <stb_image.h>
#include "Utilities.h"
#include <GL/glew.h>

// derived application class that wraps up all globals neatly
class TextureTutorial : public Application
{
public:

	TextureTutorial();
	virtual ~TextureTutorial();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	//Custom code
	struct BasicVertex
	{
		glm::vec4 position; 
		glm::vec4 colour; 
		glm::vec4 texCoord; 
	};


	GLuint m_texture; 

	BasicVertex bVertex; 

	//Buffers
	unsigned int m_VAO; 
	unsigned int m_VBO; 
	unsigned int m_IBO; 

	//Shaders
	unsigned int m_programID; 
	unsigned int m_shader; 
	unsigned int m_vertShader; 
	unsigned int m_fragShader; 
	
};