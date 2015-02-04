#include "DoorSensor.h"


CDoorSensor::CDoorSensor(I2CExpPorts sensorPort, CI2CPortExpander* portExpander)
{
	m_sensorPort = sensorPort;

	m_portExpander = portExpander;
}


CDoorSensor::~CDoorSensor()
{
}


// Returns the current sensor by reading the value on the associated sensor pin
DoorSensorState CDoorSensor::getSensorState()
{
	return (DoorSensorState)(m_portExpander->readGPIOPort(m_sensorPort));
}