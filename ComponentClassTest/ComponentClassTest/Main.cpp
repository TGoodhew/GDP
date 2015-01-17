// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "GarageDoorSenorArray.h"
#include "UltrasonicSensor.h"

CUltrasonicSensor mb1040(3, 1);

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

void setup()
{

}

// the loop routine runs over and over again forever:
void loop()
{
	mb1040.TurnSensorOn();
	delay(1000);
	mb1040.TurnSensorOff();
	delay(1000);
}