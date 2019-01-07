#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

class DeltaTime;

class Physics
{
private:
	DeltaTime* m_dTime;
	glm::vec3 m_velocity;
	glm::vec3 m_force;
	float m_mass = 1.0f;
	glm::vec3 m_gravity = glm::vec3(0.0f, 9.81f, 0.0f);

public:
	Physics(DeltaTime* _dTime);
	void UpdatePhysics();
	void Euler();



};