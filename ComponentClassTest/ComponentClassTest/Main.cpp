// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "GarageDoorSenorArray.h"
#include "UltrasonicSensor.h"

CUltrasonicSensor* mb1040;

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

void setup()
{
	mb1040 = new CUltrasonicSensor(3, 5);

	Log("Main Turn On\n");
	mb1040->TurnSensorOn();
}

// the loop routine runs over and over again forever:
void loop()
{
	Log("Main loop Distance: %d\n", mb1040->ReadSensor());
	delay(3000);
}