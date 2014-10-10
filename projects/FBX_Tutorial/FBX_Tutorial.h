#pragma once

#include "Application.h"
#include <FBXFile.h>
#include <glm/glm.hpp>

// derived application class that wraps up all globals neatly
class FBX_Tutorial : public Application
{
public:

	FBX_Tutorial();
	virtual ~FBX_Tutorial();


	
	void InitFBXSceneResource(FBXFile *a_pScene); 
	void UpdateFBXSceneResource(FBXFile *a_pScene);
	void RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void DestroyFBXSceneResource(FBXFile *a_pScene);


protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

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
};