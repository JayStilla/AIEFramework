#pragma once

#include "Application.h"
#include <FBXFile.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Utilities.h>

// derived application class that wraps up all globals neatly
class MultipleTexturesTut : public Application
{
public:

	MultipleTexturesTut();
	virtual ~MultipleTexturesTut();

	void InitFBXSceneResource(FBXFile *a_pScene);
	void UpdateFBXSceneResource(FBXFile *a_pScene);
	void RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void DestroyFBXSceneResource(FBXFile *a_pScene);

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	void LoadTexture(char * filePath);



	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	unsigned int m_shader;

	struct OGL_FBXRenderData
	{
		unsigned int VBO; //Vertex buffer object
		unsigned int IBO; //index buffer object
		unsigned int VAO; //Vertex array object
	};

	FBXFile *m_fbx;

	GLuint m_texture;
	GLuint m_texture2; 

	float m_decayValue; 
	float m_decayTexture;

	BasicVertex Swag; 

	unsigned int m_programID; 

	unsigned int m_vertShader; 
	unsigned int m_fragShader; 
};