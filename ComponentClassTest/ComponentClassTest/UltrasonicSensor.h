#pragma once
class CUltrasonicSensor
{
public:
	CUltrasonicSensor();
	~CUltrasonicSensor();
private:
	int m_SensorPowerPin;
	int m_SensorReadPin;
	int m_SensorUpTime;
public:
	// Reads the current sensor value
	int ReadSensor();
};

