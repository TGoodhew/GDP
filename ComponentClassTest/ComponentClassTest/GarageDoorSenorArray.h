#pragma once
#include "stdafx.h"
#include "arduino.h"
#include "DoorSensor.h"


typedef enum doorState
{
	DoorOpen, // Indicates that the sensor array is reading the the door is in the open position
	DoorClosed, // Indicates that the sensor array is reading the the door is in the closed position
	DoorTravelling, // Indicates that the sensor array is reading the the door is neither open or closed
} DoorState;

class CGarageDoorSenorArray
{
public:
	CGarageDoorSenorArray(int openSensorPin, int closedSensorPin);
	~CGarageDoorSenorArray();
private:
	CDoorSensor* m_DoorOpenSensor;
	CDoorSensor* m_DoorClosedSensor;
public:
	DoorState GetDoorState();
};

