#pragma once
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

class CI2CPortExpander
{
public:
	CI2CPortExpander();
	~CI2CPortExpander();
	// This function sets the IO direction for GPIO
	int setIODIR();
	// Configure the input olarity on GPIO registers
	int setIPOL();
	// Sets the IOCON register value
	int setIOCON();
	// Configures the pullup resistors for GPIO
	int setGPPU();
	// Writes to the GPIO register
	int writeGPIO();
	// Reads the GPIO register
	int readGPIO();
};

