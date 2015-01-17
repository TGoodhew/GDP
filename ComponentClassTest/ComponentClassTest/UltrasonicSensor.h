#pragma once
#include "stdafx.h"
#include "arduino.h"

#define SENSOR_ON	LOW
#define SENSOR_OFF	HIGH

class CUltrasonicSensor
{
public:
	CUltrasonicSensor(int powerPin, int readPin);
	~CUltrasonicSensor();
private:
	int m_SensorPowerPin;
	int m_SensorReadPin;
	unsigned long m_SensorUpTime;
public:
	// Reads the current sensor value
	int ReadSensor();
	void TurnSensorOn();
	void TurnSensorOff();
private:
	// This function throws away the sensor start-up information
	void WaitForValidSensorData();
};

