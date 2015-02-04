#pragma once
#include "stdafx.h"
#include "arduino.h"
#include "DoorSensor.h"
#include "I2CPortExpander.h"
#include <memory>


enum class DoorState
{
	DoorOpen, // Indicates that the sensor array is reading the the door is in the open position
	DoorClosed, // Indicates that the sensor array is reading the the door is in the closed position
	DoorTravelling, // Indicates that the sensor array is reading the the door is neither open or closed
};

class CGarageDoorSenorArray
{
public:
	CGarageDoorSenorArray(CI2CPortExpander::I2CExpPorts doorOpenSensorPort, CI2CPortExpander::I2CExpPorts doorClosedSensorPort, CI2CPortExpander* portExpander);
	~CGarageDoorSenorArray();
private:
	std::unique_ptr<CDoorSensor> m_doorOpenSensor = nullptr;
	std::unique_ptr<CDoorSensor> m_doorClosedSensor = nullptr;
public:
	DoorState GetDoorState();
};

