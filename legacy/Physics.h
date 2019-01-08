#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <string>

class DeltaTime;
class GameObject;

class Physics
{
private:
	DeltaTime* m_dTime;
	glm::vec3 m_velocity;
	glm::vec3 m_force;
	float m_mass = 1.0f;
	glm::vec3 m_gravity = glm::vec3(0.0f, 9.81f, 0.0f);
	bool IsCollider = false;
	//	COLLIDERS
	std::string m_colliderType = "Sphere";
	float m_sphereRadius = 1.0f;
	glm::vec3 m_boxDimensions = glm::vec3(1.0f, 1.0f, 1.0f);

public:
	Physics(DeltaTime* _dTime);
	std::string GetColliderType() { return m_colliderType; }
	float GetSphereRadius() { return m_sphereRadius; }
	glm::vec3 GetBoxDimentions() { return m_boxDimensions; }

	int test() { return 1; }
	void UpdatePhysics();
	void Euler();
	void CollisionUpdate(GameObject* _otherObject);

};