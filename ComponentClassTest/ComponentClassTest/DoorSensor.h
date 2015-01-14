#pragma once
#include "stdafx.h"
#include "arduino.h"

class CDoorSensor
{
public:
	CDoorSensor(int sensorPin);
	~CDoorSensor();
private:
	int m_sensorPin;
public:
	// Returns the current sensor by reading the value on the associated sensor pin
	bool getSensorState();
	// Returns the assigned value for the sensor pin
	int getSensorPin();
};

