#include "UltrasonicSensor.h"


CUltrasonicSensor::CUltrasonicSensor()
{
	m_SensorPowerPin = 0;
	m_SensorReadPin = 0;
	m_SensorUpTime = 0;
}


CUltrasonicSensor::~CUltrasonicSensor()
{
}


// Reads the current sensor value
int CUltrasonicSensor::ReadSensor()
{
	return 0;
}
