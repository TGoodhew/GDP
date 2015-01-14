#include "DoorSensor.h"


CDoorSensor::CDoorSensor(int sensorPin)
{
	// Move the sensor pin into a private member variable
	m_sensorPin = sensorPin;

	// set the pinMode of the sensor pin to be input
	pinMode(m_sensorPin, INPUT);
}


CDoorSensor::~CDoorSensor()
{
}


// Returns the current sensor by reading the value on the associated sensor pin
bool CDoorSensor::getSensorState()
{
	// Read the pin and return the bool result
	return digitalRead(m_sensorPin) != 0;
}


// Returns the assigned value for the sensor pin
int CDoorSensor::getSensorPin()
{
	return m_sensorPin;
}
