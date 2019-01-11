#include <chrono>
#include <iostream>

class DeltaTime
{
	//	note about times, they are set in seconds
	//	
private:
	 unsigned long m_initialTime;
	 unsigned long m_endTime;

	 unsigned long m_deltaTime = 16;
	 
public:
	DeltaTime();
	void SetInitialTime();
	void CalculateDeltaTime();
	unsigned long GetDeltaTime() { return m_deltaTime; }
	void SetDeltaTime(float _time) { m_deltaTime = _time; }

};