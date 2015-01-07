/*

  m2esi2c.cpp

  event source handler for an i2c connected MCP23008 port expander

  This code was based originally off the following:

  m2esserial.cpp
  
  event source handler for serial interface of arduino environment
  
  m2tklib = Mini Interative Interface Toolkit Library
  
  Copyright (C) 2012  olikraus@gmail.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#if ARDUINO < 100 
#include "wiring.h"
#include <WProgram.h> 
#else 
#include <Arduino.h> 
#include "Wire.h"
#endif

#include "m2.h"

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

// GPIO Port m2tklb key map
#define PORT_GP0_MAP	M2_KEY_NONE;
#define PORT_GP1_MAP	M2_KEY_NONE;
#define PORT_GP2_MAP	M2_KEY_SELECT;
#define PORT_GP3_MAP	M2_KEY_NEXT;
#define PORT_GP4_MAP	M2_KEY_PREV;
#define PORT_GP5_MAP	M2_KEY_EXIT;
#define PORT_GP6_MAP	M2_KEY_NONE;
#define PORT_GP7_MAP	M2_KEY_NONE;

// This function enables you to configure the MCP23008 as required for your 
// implementation (IODIR, PULLUP, etc)
extern "C" void m2_i2c_init()
{
	// Set the IO directions
	Wire.beginTransmission(MCP23008_ADDRESS);	// Device I2C address
	Wire.write(byte(MCP23008_IODIR));			// Select IODIR Register
	Wire.write(byte(PORT_GP0_MASK | PORT_GP1_MASK | PORT_GP2_MASK | PORT_GP3_MASK | PORT_GP4_MASK | PORT_GP5_MASK));			// Set GP0 - GP5 as inputs, GP6 - GP7 as outputs
	Wire.endTransmission();

	// Set the pull up resistors
	Wire.beginTransmission(MCP23008_ADDRESS);	// Device I2C address
	Wire.write(byte(MCP23008_GPPU));			// Select GPPU Register
	Wire.write(byte(PORT_GP0_MASK | PORT_GP1_MASK));			// Turn on GP0 & GP1 Resistors
	Wire.endTransmission();
}

// This function reads the current GPIO value from the MCP23008
extern "C" uint8_t m2_i2c_read()
{
	// Select the GPIO Register
	Wire.beginTransmission(MCP23008_ADDRESS);
	Wire.write(byte(MCP23008_GPIO));
	Wire.endTransmission();

	// Read the button stat
	Wire.requestFrom(MCP23008_ADDRESS, 0x01);

	if (Wire.available())
		return (uint8_t)Wire.read(); // Technically the read returns a ULONG but as this is an MCP23008 its actually a single byte
	else
		return M2_KEY_NONE;
}

/*	Take a GPIO byte and convert it into a key message
	
	m2tklib appears to be designed to take one message at a time
	so there will need to be an order defined as the GPIO byte
	will indicate multiple 'buttons' being pressed.

	Currently the order is defined simply by the port numbering
	starting from GP0 to GP7 and only if that port isn't mapped to
	return an M2_KEY_NONE.
*/
extern "C" uint8_t m2_i2c_gpio_to_key(uint8_t gpio)
{
	// TODO: Convert this into a more general usage to enable #define definition for the mappings per function comment
	if (bitRead(gpio, PORT_GP2))
		return PORT_GP2_MAP;
	if (bitRead(gpio, PORT_GP3))
		return PORT_GP3_MAP;
	if (bitRead(gpio, PORT_GP4))
		return PORT_GP4_MAP;
	if (bitRead(gpio, PORT_GP5))
		return PORT_GP5_MAP;

	return M2_KEY_NONE;
}

extern "C" uint8_t m2_es_i2c(m2_p ep, uint8_t msg)
{
  uint8_t r;
  
  switch(msg)
  {
    case M2_ES_MSG_GET_KEY:
		// Get the GPIO byte
		r = m2_i2c_read();

		//Convert it into a key message
		r = m2_i2c_gpio_to_key(r);

		return r;
    case M2_ES_MSG_INIT:
		// Initialize the Wire class
		Wire.begin();

		// Call the setup routine for the MCP23008 configuation
		// You should put all your init code in that function
		m2_i2c_init();

      return 0;
  }
  return 0;
}
