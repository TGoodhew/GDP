#include "stdafx.h"
#include "DoorSensor.h"


CDoorSensor::CDoorSensor(CI2CPortExpander::I2CExpPorts sensorPort, CI2CPortExpander* portExpander)
{
	m_sensorPort = sensorPort;

	m_portExpander = portExpander;

	// Set the port on the port expander to be input
	portExpander->setIODIR(sensorPort, CI2CPortExpander::I2CExpIODirection::Input, true);
}


CDoorSensor::~CDoorSensor()
{
}


// Returns the current sensor by reading the value on the associated sensor pin
DoorSensorState CDoorSensor::getSensorState()
{
	return (DoorSensorState)(m_portExpander->readGPIOPort(m_sensorPort));
}