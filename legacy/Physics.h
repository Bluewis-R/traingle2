#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <string>

const float E = 2.718281;

class DeltaTime;
class GameObject;

class Physics
{
private:
	GameObject * m_gameObject;

	DeltaTime* m_dTime;
	glm::vec3 m_velocity;
	glm::vec3 m_force;
	float m_mass = 1.0f;
	glm::vec3 m_gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	bool m_static = false;
	bool IsCollider = false;
	bool m_grounded = false;
	//	COLLIDERS
	std::string m_colliderType = "Sphere";
	float m_sphereRadius = 1.0f;
	glm::vec3 m_boxDimensions = glm::vec3(1.0f, 1.0f, 1.0f);

public:
	Physics(GameObject* _gameObject, DeltaTime* _dTime);
	std::string GetColliderType() { return m_colliderType; }
	void SetColliderType(std::string _string) { m_colliderType = _string; }
	float GetSphereRadius() { return m_sphereRadius; }
	glm::vec3 GetVelocity() { return m_velocity; }
	void SetVelocity(glm::vec3 _vel) { m_velocity = _vel; }
	glm::vec3 GetForce() { return m_force; }
	void SetForce(glm::vec3 _for) { m_force = _for; };
	float GetMass() { return m_mass; }
	void SetGrounded(bool _g) { m_grounded = _g; }
	glm::vec3 GetBoxDimentions() { return m_boxDimensions; }
	void SetStatic(bool _bool) { m_static = true; }
	void SetG(glm::vec3 _g) { m_gravity = _g; }
	int test() { return 1; }
	void UpdatePhysics();
	void Euler();
	void CollisionUpdateSTS(GameObject* _otherObject, GameObject* _gameObject2, glm::vec3 _contactPoint);

	void CollisionUpdateSTP(GameObject* _otherObject, GameObject* _plane);

};