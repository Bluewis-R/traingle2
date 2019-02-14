#include "SimplePhysics.h"
#include "GameObject.h"
#include "DeltaTime.h"


//	Constuctor things.
SimplePhysics::SimplePhysics(GameObject* _gameObject, DeltaTime* _deltaTime)
{
	m_gameObject = _gameObject;
	m_deltaTime = _deltaTime;
}

//	This add simple gravity and collision detections with
//	the artificial floor.
void SimplePhysics::UpdatePhysics()
{
	if (m_gameObject->GetPosition().y > 33.6f)
	{
		m_velocity -= glm::vec3(0.0f, m_gravity*m_deltaTime->GetDeltaTime()/1000.0f, 0.0f);
		glm::vec3 oldPos = m_gameObject->GetPosition();
		glm::vec3 newPos = oldPos + (m_velocity * ((float)m_deltaTime->GetDeltaTime())/1000.0f);
		
		m_gameObject->SetPosition(newPos);

		m_airborn = true;
	}
	else
	{
 		m_airborn = false;
	}

}