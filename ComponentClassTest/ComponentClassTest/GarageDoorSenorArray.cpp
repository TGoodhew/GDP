#include "GarageDoorSenorArray.h"


CGarageDoorSenorArray::CGarageDoorSenorArray(int openSensorPin, int closedSensorPin)
{
	m_DoorOpenSensor = new CDoorSensor(openSensorPin);
	m_DoorClosedSensor = new CDoorSensor(closedSensorPin);
}


CGarageDoorSenorArray::~CGarageDoorSenorArray()
{
	delete m_DoorOpenSensor;
	delete m_DoorClosedSensor;
}


DoorState CGarageDoorSenorArray::GetDoorState()
{
	bool doorOpen, doorClosed;

	// Read the door sensors
	doorOpen = m_DoorOpenSensor->getSensorState();
	doorClosed = m_DoorClosedSensor->getSensorState();

	// return the appropriate door state
	if (doorOpen && !doorClosed)
		return DoorOpen;
	else if (doorClosed && !doorOpen)
		return DoorClosed;
	else
		return DoorTravelling;
}
