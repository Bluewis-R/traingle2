#include "PhysicsManager.h"


#include "ObjectManager.h"
#include "GameObject.h"
#include "Physics.h"

PhysicsManager::PhysicsManager(ObjectManager* _objectManager)
{
	for (int i = 0; i < _objectManager->NumberOfObjects(); i++)
	{
		if (_objectManager->GetGameObject(i)->GetPhysics() != NULL)
		{
			m_physicsObjects.push_back(_objectManager->GetGameObject(i));
		}
	}
}

PhysicsManager::~PhysicsManager()
{
	{
		for (std::vector< GameObject* >::iterator it = m_physicsObjects.begin(); it != m_physicsObjects.end(); ++it)
		{
			delete (*it);
		}
		m_physicsObjects.clear();
	}
}


//This Function Itterates thought all objects and checks Sphere to Sphere and 
//	Sphere to Plane collisions then finally running the Euler intergration
void PhysicsManager::UpdatingThroughPhysicsObjets()
{
	for (int i = 0; i < m_physicsObjects.size(); i++)
	{
		bool i_ground = false;

		m_physicsObjects.at(i)->GetPhysics()->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
		for (int j = i + 1; j < m_physicsObjects.size(); j++)
		{
			std::string obj1 = m_physicsObjects.at(i)->GetPhysics()->GetColliderType();
			std::string obj2 = m_physicsObjects.at(j)->GetPhysics()->GetColliderType();
			//	Sphere to Sphere
			if (obj1 == "Sphere" && obj2 == "Sphere")
			{
				glm::vec3 contactPoint = glm::vec3(0.0f, 0.0f, 0.0f);
				if (SphereToSphere(i, j, contactPoint))
				{
					//std::cout << "STS Collision" << std::endl;
					m_physicsObjects.at(i)->GetPhysics()->SetGrounded(true);
					m_physicsObjects.at(j)->GetPhysics()->SetGrounded(true);
					m_physicsObjects.at(i)->GetPhysics()->CollisionUpdateSTS(m_physicsObjects.at(j), m_physicsObjects.at(i), contactPoint);
					m_physicsObjects.at(j)->GetPhysics()->CollisionUpdateSTS(m_physicsObjects.at(i), m_physicsObjects.at(j), contactPoint);
				}
				else
				{
					m_physicsObjects.at(j)->GetPhysics()->SetGrounded(false);
				}

			}
			//	Sphere to Plane
			else if ((obj1 == "Sphere" && obj2 == "Plane") || (obj1 == "Plane" && obj2 == "Sphere")) 
			{
				if (m_physicsObjects.at(i)->GetPhysics()->GetColliderType() == "Plane")
				{
					int k = i;
					i = j;
					j = i;
				}

				// is it the sphere
				glm::vec3 contactPoint = glm::vec3(0.0f, 0.0f, 0.0f);
				if (SphereToPlane(i, j, contactPoint))
				{					
					//std::cout << "Plane Collision" << std::endl;
					m_physicsObjects.at(i)->GetPhysics()->SetGrounded(true);

					m_physicsObjects.at(i)->GetPhysics()->CollisionUpdateSTP(m_physicsObjects.at(i), m_physicsObjects.at(j));
					//m_physicsObjects.at(i)->GetPhysics()->SetForce(m_physicsObjects.at(i)->GetPhysics()->GetForce() + 1.0f);
				}
				else
				{
					m_physicsObjects.at(j)->GetPhysics()->SetGrounded(false);
				}


			}

		

			//m_physicsObjects.at(j)->GetPhysics()->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
		}
		if (!i_ground) { m_physicsObjects.at(i)->GetPhysics()->SetGrounded(false); }

		m_physicsObjects.at(i)->GetPhysics()->UpdatePhysics();

	}
}

bool PhysicsManager::SphereToSphere(int _i, int _j, glm::vec3& _cp)
{
	glm::vec3 c0 = m_physicsObjects.at(_i)->GetPosition();
	glm::vec3 c1 = m_physicsObjects.at(_j)->GetPosition();
	float a = m_physicsObjects.at(_j)->GetPhysics()->GetSphereRadius();
	float b = m_physicsObjects.at(_j)->GetPhysics()->GetSphereRadius();
	//glm::vec3 _cp;
	return Util::STS(c0, c1, a, b, _cp);
	
	//	My old method
	/*
	glm::vec3 i_pos = m_physicsObjects.at(_i)->GetPosition();
	glm::vec3 j_pos = m_physicsObjects.at(_j)->GetPosition();
	float i_radius = m_physicsObjects.at(_i)->GetPhysics()->GetSphereRadius();
	float j_radius = m_physicsObjects.at(_j)->GetPhysics()->GetSphereRadius();
	glm::vec3 dif = glm::vec3(i_pos.x - j_pos.x, i_pos.y - j_pos.y, i_pos.y - j_pos.y);
	float distance = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2) );

	if (distance > i_radius + j_radius)
	{
		return true;
	}
	return false;
	*/
}

bool PhysicsManager::SphereToPlane(int _i, int _j, glm::vec3& _cp)
{
	glm::vec3 p, q, n;
	GameObject*	sphere;
	n = glm::vec3(0.0f, 1.0f, 0.0f);
	

	p = m_physicsObjects.at(_i)->GetPosition();
	q = m_physicsObjects.at(_j)->GetPosition();
	sphere = m_physicsObjects.at(_i);

	float distance = Util::DistanceToPlane(p, q, n);
	
	_cp = p + n * distance;



	if (abs(distance) < sphere->GetPhysics()->GetSphereRadius())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//	
//	
//	
//	
//	Util section
//	
//	
//	
//	
float Util::DistanceToPlane(const glm::vec3& p, const glm::vec3& q, const glm::vec3& n)
{
	float d = glm::dot((p - q), n);
	return d;
}

	//	
	//	cp is contact point
bool Util::STS(const glm::vec3& c0, const glm::vec3& c1, float r1, float r2, glm::vec3& cp)
{
	float d = glm::length(c0 - c1);
	glm::vec3 n;
	if (d <= (r1 + r2))
	{
		n = glm::normalize(c0 - c1);
		cp = r1 + n;
		return true;
	}
	return false;
}
