#ifndef _PARTICLE_SYSTEM_
#define _PARTICLE_SYSTEM_

#include "Application.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <stb_image.h>
#include <Utilities.h>
#include <GL\glew.h>
#include <list>

//Creating structs
struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 colour;
	float size;
	float lifetime;
	float lifespan;
};

struct ParticleVertex
{
	glm::vec4 position;
	glm::vec4 colour;
};

class ParticleSystem
{
public:
	ParticleSystem(); 
	virtual ~ParticleSystem();

	//initialise the particle emitter
	void initalise(unsigned int a_maxParticles, unsigned int a_emitRate,
		float a_lifetimeMin, float a_lifetimeMax,
		float a_velocityMin, float a_velocityMax,
		float a_startSize, float a_endSize,
		const glm::vec4& a_startColour, const glm::vec4& a_endColour);

	//emit particles
	void emit(); 
	void update(float a_deltaTime, const glm::mat4& a_cameraTransform);
	void draw();

protected:
	std::list<Particle*> m_aliveParticles; 
	std::list<Particle*> m_deadParticles; 
	Particle* m_particles; 

	unsigned int m_VAO, m_VBO, m_IBO;
	ParticleVertex* m_vertexData; 
	unsigned int* m_indexData; 

	glm::vec3 m_position; 

	float m_emitTimer; 
	float m_emitRate; 

	float m_lifespanMin; 
	float m_lifespanMax; 

	float m_velocityMin;
	float m_velocityMax;

	float m_startSize; 
	float m_endSize; 

	glm::vec4 m_startColour; 
	glm::vec4 m_endColour; 
};






#endif 