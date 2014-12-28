// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "spi.h"

#define SPI_Enable	10

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

void setup()
{
	pinMode(SPI_Enable, OUTPUT);
	digitalWrite(SPI_Enable, HIGH);
	SPI.setClockDivider(SPI_CLOCK_DIV16);
	SPI.begin();
}

// the loop routine runs over and over again forever:
void loop()
{
	digitalWrite(SPI_Enable, LOW);
	SPI.transfer(83);
	SPI.transfer(72);
	digitalWrite(SPI_Enable, HIGH);
	delay(1);
}