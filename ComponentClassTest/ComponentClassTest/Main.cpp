// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "GarageDoorSenorArray.h"
#include "UltrasonicSensor.h"
#include "I2CPortExpander.h"
#include "Relay.h"
#include "DoorSensor.h"

CUltrasonicSensor* mb1040;
CI2CPortExpander* mcp23008;
CRelay* relay;
CDoorSensor* doorSensor;
CGarageDoorSenorArray* doorSensorArray;

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

void setup()
{
	I2CExpPorts relayPorts[2];

	relayPorts[0] = I2CExpPorts::PORT_GP6;
	relayPorts[1] = I2CExpPorts::PORT_GP7;

	//mb1040 = new CUltrasonicSensor(3, 5);

	//Log("Main Turn On\n");
	//mb1040->TurnSensorOn();

	Wire.begin();

	mcp23008 = new CI2CPortExpander();

	mcp23008->setIODIR(I2CExpPorts::PORT_GP0, I2CExpIODirection::Input, true);
	mcp23008->setIODIR(I2CExpPorts::PORT_GP1, I2CExpIODirection::Input, true);
	mcp23008->setIODIR(I2CExpPorts::PORT_GP6, I2CExpIODirection::Output, true);
	mcp23008->setIODIR(I2CExpPorts::PORT_GP7, I2CExpIODirection::Output, true);

	relay = new CRelay(2, relayPorts, 6, mcp23008);

	//doorSensor = new CDoorSensor(I2CExpPorts::PORT_GP0, mcp23008);

	doorSensorArray = new CGarageDoorSenorArray(I2CExpPorts::PORT_GP0, I2CExpPorts::PORT_GP1, mcp23008);
}

// the loop routine runs over and over again forever:
void loop()
{
	//Log("Main loop Distance: %d\n", mb1040->ReadSensor());
	//delay(3000);

	//mcp23008->writeGPIO(I2CExpPorts::PORT_GP7, I2CExpGPIOValue::Low, false);
	//mcp23008->writeGPIO(I2CExpPorts::PORT_GP6, I2CExpGPIOValue::High, true);
	//Log("GPIO Value: %X\n", mcp23008->readGPIO());
	//delay(1000);

	//mcp23008->writeGPIO(I2CExpPorts::PORT_GP6, I2CExpGPIOValue::Low, false);
	//mcp23008->writeGPIO(I2CExpPorts::PORT_GP7, I2CExpGPIOValue::High, true);
	//Log("GPIO Value: %X\n", mcp23008->readGPIO());
	//delay(1000);

	//relay->openRelayChannel(0);
	//relay->closeRelayChannel(1);
	//delay(1000);
	//relay->closeRelayChannel(0);
	//relay->openRelayChannel(1);
	//delay(1000);

	//Log("Door Sensor value: %d\n", doorSensor->getSensorState());
	//delay(1000);

	Log("Garage door sensor array state: %d\n", doorSensorArray->GetDoorState());
	delay(1000);
}