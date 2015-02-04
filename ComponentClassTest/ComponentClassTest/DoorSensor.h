#pragma once
#include "stdafx.h"
#include "arduino.h"
#include "I2CPortExpander.h"

enum class DoorSensorState
{
	Open = 0,
	Closed = 1
};

class CDoorSensor
{
public:
	CDoorSensor(CI2CPortExpander::I2CExpPorts sensorPort, CI2CPortExpander* portExpander);
	~CDoorSensor();
private:
	CI2CPortExpander::I2CExpPorts m_sensorPort;
	CI2CPortExpander* m_portExpander = nullptr;
public:
	// Returns the current sensor by reading the value on the associated sensor pin
	DoorSensorState getSensorState();
};

