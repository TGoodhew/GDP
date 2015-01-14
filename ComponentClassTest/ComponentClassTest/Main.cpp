// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "GarageDoorSenorArray.h"

CGarageDoorSenorArray door(1, 2);

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

}