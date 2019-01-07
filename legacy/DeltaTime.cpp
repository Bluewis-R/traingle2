#include "DeltaTime.h"

DeltaTime::DeltaTime()
{
	//	Initilises the end point,
	//	note for future: m_initialTime may need to be initilised 
	CalculateDeltaTime();	

	unsigned long k = GetDeltaTime();


}

void DeltaTime::SetInitialTime()
{
	m_initialTime = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
}

void DeltaTime::CalculateDeltaTime()
{
	m_endTime = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	m_deltaTime = (m_endTime - m_initialTime);
}