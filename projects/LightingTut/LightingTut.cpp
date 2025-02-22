#include "LightingTut.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

DirectionalLight light; 

LightingTut::LightingTut()
{

}

LightingTut::~LightingTut()
{

}

bool LightingTut::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();
	
	light.AmbientLight = glm::vec3(0.1, 0.1, 0.1);
	light.LightColour = glm::vec3(1, 1, 1);
	light.LightDirection = glm::vec3(-1, 0, 1);
	light.LightSpecular = glm::vec3(0, 10, 0);

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );

	// get window dimensions to calculate aspect ratio
	int width = 0, height = 0;
	glfwGetWindowSize(m_window, &width, &height);

	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, width / (float)height, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	//custom code
	//m_vertShader = Utility::loadShader("shaders/lit.vert", GL_VERTEX_SHADER); 
	//m_fragShader = Utility::loadShader("shaders/lit.frag", GL_FRAGMENT_SHADER);

	//const char* inputs[] = { "Position" };
	//m_shader = Utility::createProgram(m_vertShader, 0, 0, 0, m_fragShader, 1, inputs);

	// load shaders and link shader program
	m_vertShader = Utility::loadShader("./shaders/lit.vert", GL_VERTEX_SHADER);
	m_fragShader = Utility::loadShader("./shaders/lit.frag", GL_FRAGMENT_SHADER);
	const char* inputs[] = { "Position", "Normal" };
	m_shader = Utility::createProgram(m_vertShader, 0, 0, 0, m_fragShader, 2, inputs);

	m_fbx = new FBXFile();
	m_fbx->load("./Models/stanford/Bunny.fbx");

	createOpenGLBuffers(m_fbx);

	return true;
}

void LightingTut::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// add a 20x20 grid on the XZ-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void LightingTut::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(m_projectionMatrix, viewMatrix);

	// get window dimensions for 2D orthographic projection
	int width = 0, height = 0;
	glfwGetWindowSize(m_window, &width, &height);
	Gizmos::draw2D(glm::ortho<float>(0, width, 0, height, -1.0f, 1.0f));

	//Custom Code
	//bind shader to the GPU
	glUseProgram(m_shader); 

	//fetch locations of the view and projection matrices and bind them
	unsigned int location = glGetUniformLocation(m_shader, "view"); 
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(viewMatrix)); 

	location = glGetUniformLocation(m_shader, "projection");
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(m_projectionMatrix));

	//send camera position 
	location = glGetUniformLocation(m_shader, "cameraPosition");
	glUniform3fv(location, 1, glm::value_ptr(m_cameraMatrix[3]));

	location = glGetUniformLocation(m_shader, "lightAmbient"); 
	glUniform3fv(location, 1, glm::value_ptr(light.AmbientLight));

	location = glGetUniformLocation(m_shader, "lightDirection");
	glUniform3fv(location, 1, glm::value_ptr(light.LightDirection));

	location = glGetUniformLocation(m_shader, "lightColour");
	glUniform3fv(location, 1, glm::value_ptr(light.LightColour));

	location = glGetUniformLocation(m_shader, "lightSpecular"); 
	glUniform3fv(location, 1, glm::value_ptr(light.LightSpecular));

	// bind our vertex array object and draw the mesh
	for (unsigned int i = 0; i < m_fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = m_fbx->getMeshByIndex(i);

		unsigned int* glData = (unsigned int*)mesh->m_userData;

		glBindVertexArray(glData[0]);
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}

}

void LightingTut::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();

	//Custom Code
	//Deleting shaders
	glDeleteProgram(m_shader);
	glDeleteShader(m_vertShader);
	glDeleteShader(m_fragShader);
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	Application* app = new LightingTut();
	
	if (app->create("AIE - LightingTut",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}

//Custom Function
void LightingTut::createOpenGLBuffers(FBXFile* a_fbx)
{
	//create the GL VAO/VBO/IBO data for the meshes
	for (unsigned int i = 0; i < a_fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = a_fbx->getMeshByIndex(i);

		//storage for the opengl data in 3 unsigned int
		unsigned int* glData = new unsigned int[3];

		glGenVertexArrays(1, &glData[0]);
		glBindVertexArray(glData[0]);

		glGenBuffers(1, &glData[1]);
		glGenBuffers(1, &glData[2]);

		glBindBuffer(GL_ARRAY_BUFFER, glData[1]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData[2]);

		glBufferData(GL_ARRAY_BUFFER, mesh->m_vertices.size() * sizeof(FBXVertex), mesh->m_vertices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->m_indices.size() * sizeof(unsigned int), mesh->m_indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0); // position
		glEnableVertexAttribArray(1); // normal
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(FBXVertex), ((char*)0) + FBXVertex::NormalOffset);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		mesh->m_userData = glData;
	}
}

void LightingTut::cleanupOpenGLBuffers(FBXFile* a_fbx)
{
	//bind our vertex array object and draw the mesh
	for (unsigned int i = 0; i < a_fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = a_fbx->getMeshByIndex(i); 

		unsigned int* glData = (unsigned int*)mesh->m_userData; 

		glDeleteVertexArrays(1, &glData[0]);
		glDeleteBuffers(1, &glData[1]);
		glDeleteBuffers(1, &glData[2]);

		delete[] glData; 

	}
}