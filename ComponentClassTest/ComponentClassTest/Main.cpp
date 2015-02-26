// Main.cpp : Defines the entry point for the console application.
//

// includes - Add these directories to the project file include directories:
// Repos\u8glib\cppsrc
// Repos\u8glib\csrc
// Repos\m2tklib\cpp
// Repos\m2tklib\src
// Repos\m2tklib\dev\u8glib
//
#include "stdafx.h"
#include "arduino.h"
#include <ctime>
#include "CoreDevices.h"
#include "UserInterface.h"

// Core device variables
CUltrasonicSensor* mb1040;
CI2CPortExpander* mcp23008;
CRelay* relay;
CDoorSensor* doorSensor;
CGarageDoorSenorArray* doorSensorArray;
CButtonArray* buttonArray;


int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

// Initialize the hardware that the test harness uses
void initializeHW()
{
	// HW is a 2 channel relay and 4 buttons connected to an I2C port expander
	// these arrays will hold the ports on the I2C port exander that connect the relay and buttons
	CI2CPortExpander::I2CExpPorts relayPorts[2];
	CI2CPortExpander::I2CExpPorts buttonPorts[4];

	// Define the ports on the I2C port expander for the relay as each port controls an individual channel
	relayPorts[0] = CI2CPortExpander::I2CExpPorts::PORT_GP6;
	relayPorts[1] = CI2CPortExpander::I2CExpPorts::PORT_GP7;

	// Create a new CUltraSonicSensor instance and connect it to the power pin (3) and the control pin (5) on the Galileo
	mb1040 = new CUltrasonicSensor(3, 5);

	// Turn the sensor on
	mb1040->TurnSensorOn();

	// Setup the I2C connection
	Wire.begin();

	// Create a new CI2CPortExpander instance
	mcp23008 = new CI2CPortExpander();

	// Create a new CRelay instance and hook up (Channels, Port Expander Ports, Power Pin, Port Expander)
	relay = new CRelay(2, relayPorts, 6, mcp23008);

	// Create a new CGarageDoorSensorArray instance and hook up (Open Sensor, Close Sensor, Port Expander)
	doorSensorArray = new CGarageDoorSenorArray(CI2CPortExpander::I2CExpPorts::PORT_GP0, CI2CPortExpander::I2CExpPorts::PORT_GP1, mcp23008);

	// Define the ports that the buttons are connected to
	buttonPorts[0] = CI2CPortExpander::I2CExpPorts::PORT_GP2;
	buttonPorts[1] = CI2CPortExpander::I2CExpPorts::PORT_GP3;
	buttonPorts[2] = CI2CPortExpander::I2CExpPorts::PORT_GP4;
	buttonPorts[3] = CI2CPortExpander::I2CExpPorts::PORT_GP5;

	// Create a new CButtonArray instance and hook up (Number of buttons, Port Expander Ports, Port Expander)
	buttonArray = new CButtonArray(4, buttonPorts, mcp23008);
}

void setup()
{
	// Allocate some memory for a label string and set it to zero
	str = (char *)malloc(512);
	memset(str, 0, 512);

	// Connect u8glib with m2tklib
	m2_SetU8g(u8g.getU8g(), m2_u8g_box_icon);

	// Assign u8g font to index 0 */
	m2.setFont(0, u8g_font_7x13);

	// Call the picture loop to display the splash screen and tell it not to take key input at this time
	pictureLoop(false);

	// Initialize the hardware now that the splash screen is displaying
	initializeHW();

	// Once initialization is done set the menuing system to display the main menu
	m2.setRoot(&el_main_vlist);
}

// the loop routine runs over and over again forever:
void loop()
{
	// Call the picture loop and handle keys - The picture loop not only displays the menuing system it will also drive the state machine
	pictureLoop();
}

/*
*	m2tklib event source
*	
*	This is hooked up to the m2tklib main object and gets called when it does a checkKey() call.
*	In the case here there are 4 inputs connected to ports on the port expander. The m2tklib
*	event handler for this is m2eh4bs.c.
*	
*	Detail on the different event handlers is available here https://code.google.com/p/m2tklib/wiki/fnref#M2tk
*/
extern "C" uint8_t m2_es_i2c(m2_p ep, uint8_t msg)
{
	uint8_t keyMessage = M2_KEY_NONE;

	switch (msg)
	{
	case M2_ES_MSG_GET_KEY:
		if (buttonArray->readButton(0) == CButton::ButtonState::Closed)
			return M2_KEY_SELECT;
		if (buttonArray->readButton(1) == CButton::ButtonState::Closed)
			return M2_KEY_NEXT;
		if (buttonArray->readButton(2) == CButton::ButtonState::Closed)
			return M2_KEY_PREV;
		if (buttonArray->readButton(3) == CButton::ButtonState::Closed)
			return M2_KEY_EXIT;

		return keyMessage;

	}

	return 0;
}

