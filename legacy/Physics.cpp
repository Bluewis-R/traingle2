#include "Physics.h"

#include "DeltaTime.h"
#include "GameObject.h"

Physics::Physics(GameObject* _gameOBject, DeltaTime* _dTime)
{
	m_dTime = _dTime;
	m_gameObject = _gameOBject;
}

//	If the object in question is not static Euler intergration
//	is applied and if the object is colliding gravity is not applied
void Physics::UpdatePhysics()
{
	if (!m_static)
	{
		if (!m_grounded)
		{
			m_force += m_gravity;
		}
		Euler();
	}
}

void Physics::Euler()
{
	// Vcurrent = Vprivious + (F/m) * Dt;
	// Pcurrent = Pprevious + Velocity * Dt
	m_velocity += (m_force / m_mass) * (((float)m_dTime->GetDeltaTime()) / 1000.0f);
	m_gameObject->SetPosition(m_gameObject->GetPosition() + m_velocity * (((float)m_dTime->GetDeltaTime()) / 1000.0f));
}

//	The impulse of a sphere is calculated and the force of the
//	sphere is applied
void Physics::CollisionUpdateSTS(GameObject* _gameObject, GameObject* _gameObject2, glm::vec3 _contactPoint)
{
	glm::vec3 va = _gameObject->GetPhysics()->GetVelocity();
	glm::vec3 vb = _gameObject2->GetPhysics()->GetVelocity();
	float ma = _gameObject->GetPhysics()->GetMass();
	float mb = _gameObject2->GetPhysics()->GetMass();
	glm::vec3 n = _contactPoint - va;

	float t = (n.x + n.y + n.z);
	n /= t;

	float temp1 = glm::dot(-(1 - E)*(va - vb), n);
	float temp2 = 1.0f*(1.0f / (ma)) + (1.0f / (mb));

	float temp3 = temp1 / temp2;


	n = n*temp3;

	std::cout << _gameObject->GetPhysics()->GetForce().y;

	_gameObject->GetPhysics()->SetForce(_gameObject->GetPhysics()->GetForce()+(-1.0f*n));
}


//	This Sphere to sphere collision update reverses the direction
//	of the force of a sphere reacting agaist a plane
void Physics::CollisionUpdateSTP(GameObject* _gameObject, GameObject* _plane)
{
	_gameObject->GetPhysics()->SetForce(glm::vec3(1.0f,-0.9f, 1.0f)*_gameObject->GetPhysics()->GetForce());
}