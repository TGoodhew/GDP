// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "GarageDoorSenorArray.h"
#include "UltrasonicSensor.h"
#include "I2CPortExpander.h"

CUltrasonicSensor* mb1040;
CI2CPortExpander* mcp23008;

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

void setup()
{
	//mb1040 = new CUltrasonicSensor(3, 5);

	//Log("Main Turn On\n");
	//mb1040->TurnSensorOn();

	Wire.begin();

	mcp23008 = new CI2CPortExpander();

	mcp23008->setIODIR(I2CExpPorts::PORT_GP6, I2CExpIODirection::Output, true);
	mcp23008->setIODIR(I2CExpPorts::PORT_GP7, I2CExpIODirection::Output, true);
}

// the loop routine runs over and over again forever:
void loop()
{
	//Log("Main loop Distance: %d\n", mb1040->ReadSensor());
	//delay(3000);

	mcp23008->writeGPIO(I2CExpPorts::PORT_GP7, I2CExpGPIOValue::Low, false);
	mcp23008->writeGPIO(I2CExpPorts::PORT_GP6, I2CExpGPIOValue::High, true);
	Log("GPIO Value: %X\n", mcp23008->readGPIO());
	delay(1000);

	mcp23008->writeGPIO(I2CExpPorts::PORT_GP6, I2CExpGPIOValue::Low, false);
	mcp23008->writeGPIO(I2CExpPorts::PORT_GP7, I2CExpGPIOValue::High, true);
	Log("GPIO Value: %X\n", mcp23008->readGPIO());
	delay(1000);

}