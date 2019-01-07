#include "Physics.h"

#include "DeltaTime.h"

Physics::Physics(DeltaTime* _dTime)
{
	std::cout << "Physics constructor";
	m_dTime = _dTime;
}

void Physics::UpdatePhysics()
{
	m_force += m_gravity;
}

void Physics::Euler()
{
	// Vcurrent = Vprivious + (F/m) *Dt;
	m_velocity += (m_force / m_mass) * (float)(m_dTime->GetDeltaTime());
}