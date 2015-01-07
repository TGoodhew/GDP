// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "wire.h"

// Base address of device
#define MCP23008_ADDRESS 0x20

// Registers
#define MCP23008_IODIR 0x00
#define MCP23008_IPOL 0x01
#define MCP23008_GPINTEN 0x02
#define MCP23008_DEFVAL 0x03
#define MCP23008_INTCON 0x04
#define MCP23008_IOCON 0x05
#define MCP23008_GPPU 0x06
#define MCP23008_INTF 0x07
#define MCP23008_INTCAP 0x08
#define MCP23008_GPIO 0x09
#define MCP23008_OLAT 0x0A

// GPIO Masks
#define PORT_GP0_MASK	0x01
#define PORT_GP1_MASK	0x02
#define PORT_GP2_MASK	0x04
#define PORT_GP3_MASK	0x08
#define PORT_GP4_MASK	0x10
#define PORT_GP5_MASK	0x20
#define PORT_GP6_MASK	0x40
#define PORT_GP7_MASK	0x80

// GPIO Port Bits
#define PORT_GP0	0
#define PORT_GP1	1
#define PORT_GP2	2
#define PORT_GP3	3
#define PORT_GP4	4
#define PORT_GP5	5
#define PORT_GP6	6
#define PORT_GP7	7

int keyVal = 0;


int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

void setup()
{
	// Setup the wrie class
	Wire.begin();

	// Set the IO directions
	Wire.beginTransmission(0x20);	// Device I2C address
	Wire.write(byte(MCP23008_IODIR));			// Select IODIR Register
	Wire.write(byte(PORT_GP0_MASK | PORT_GP1_MASK | PORT_GP2_MASK | PORT_GP3_MASK | PORT_GP4_MASK | PORT_GP5_MASK));			// Set GP0 - GP5 as inputs, GP6 - GP7 as outputs
	Wire.endTransmission();

	// Set the pull up resistors
	Wire.beginTransmission(0x20);	// Device I2C address
	Wire.write(byte(MCP23008_GPPU));			// Select GPPU Register
	Wire.write(byte(PORT_GP0_MASK | PORT_GP1_MASK));			// Turn on GP0 & GP1 Resistors
	Wire.endTransmission();
}

// the loop routine runs over and over again forever:
void loop()
{
	// Select the GPIO Register
	Wire.beginTransmission(0x20);
	Wire.write(byte(MCP23008_GPIO));
	Wire.endTransmission();

	// Read the button stat
	Wire.requestFrom(0x20, 0x01);

	while (Wire.available())
	{
		keyVal = Wire.read();

		if (bitRead(keyVal, PORT_GP0))
			Log("Door Switch 1\n");
		if (bitRead(keyVal, PORT_GP1))
			Log("Door Switch 2\n");
		if (bitRead(keyVal, PORT_GP2))
		{
			Log("Button 1 Pressed\n");
			// Select the GPIO Register
			Wire.beginTransmission(0x20);
			Wire.write(byte(MCP23008_GPIO));
			Wire.write(byte(bitSet(keyVal, PORT_GP6)));
			Wire.endTransmission();

			Log("Relay 1 High(%d)\n", keyVal);
		}
			
		if (bitRead(keyVal, PORT_GP3))
		{
			Log("Button 2 Pressed\n");
			// Select the GPIO Register
			Wire.beginTransmission(0x20);
			Wire.write(byte(MCP23008_GPIO));
			Wire.write(byte(bitClear(keyVal, PORT_GP6)));
			Wire.endTransmission();

			Log("Relay 1 Low(%d)\n", keyVal);
		}
		if (bitRead(keyVal, PORT_GP4))
		{
			Log("Button 3 Pressed\n");

			// Select the GPIO Register
			Wire.beginTransmission(0x20);
			Wire.write(byte(MCP23008_GPIO));
			Wire.write(byte(bitSet(keyVal, PORT_GP7)));
			Wire.endTransmission();

			Log("Relay 2 High(%d)\n", keyVal);
		}
		if (bitRead(keyVal, PORT_GP5))
		{
			Log("Button 4 Pressed\n");

			// Select the GPIO Register
			Wire.beginTransmission(0x20);
			Wire.write(byte(MCP23008_GPIO));
			Wire.write(byte(bitClear(keyVal, PORT_GP7)));
			Wire.endTransmission();

			Log("Relay 2 Low(%d)\n", keyVal);
		}
		
		Log("End Loop\n");
	}

	delay(50);

}