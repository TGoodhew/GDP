#include "stdafx.h"
#include "GarageDoorSenorArray.h"


CGarageDoorSenorArray::CGarageDoorSenorArray(CI2CPortExpander::I2CExpPorts doorOpenSensorPort, CI2CPortExpander::I2CExpPorts doorClosedSensorPort, CI2CPortExpander* portExpander)
{
	m_doorOpenSensor = std::make_unique<CDoorSensor>(doorOpenSensorPort, portExpander);
	m_doorClosedSensor = std::make_unique<CDoorSensor>(doorClosedSensorPort, portExpander);
}


CGarageDoorSenorArray::~CGarageDoorSenorArray()
{

}


DoorState CGarageDoorSenorArray::GetDoorState()
{
	DoorSensorState openSensor, closedSensor;

	openSensor = m_doorOpenSensor->getSensorState();
	closedSensor = m_doorClosedSensor->getSensorState();

	if ((openSensor == DoorSensorState::Open) && (closedSensor == DoorSensorState::Closed))
		return DoorState::DoorClosed;
	else if ((openSensor == DoorSensorState::Closed) && (closedSensor == DoorSensorState::Open))
		return DoorState::DoorOpen;
	else
		return DoorState::DoorTravelling;
}
