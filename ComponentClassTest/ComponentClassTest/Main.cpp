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

void initializeHW()
{
	CI2CPortExpander::I2CExpPorts relayPorts[2];
	CI2CPortExpander::I2CExpPorts buttonPorts[4];

	relayPorts[0] = CI2CPortExpander::I2CExpPorts::PORT_GP6;
	relayPorts[1] = CI2CPortExpander::I2CExpPorts::PORT_GP7;

	mb1040 = new CUltrasonicSensor(3, 5);

	Log("Main Turn On\n");
	mb1040->TurnSensorOn();

	Wire.begin();

	mcp23008 = new CI2CPortExpander();

	relay = new CRelay(2, relayPorts, 6, mcp23008);

	doorSensorArray = new CGarageDoorSenorArray(CI2CPortExpander::I2CExpPorts::PORT_GP0, CI2CPortExpander::I2CExpPorts::PORT_GP1, mcp23008);

	buttonPorts[0] = CI2CPortExpander::I2CExpPorts::PORT_GP2;
	buttonPorts[1] = CI2CPortExpander::I2CExpPorts::PORT_GP3;
	buttonPorts[2] = CI2CPortExpander::I2CExpPorts::PORT_GP4;
	buttonPorts[3] = CI2CPortExpander::I2CExpPorts::PORT_GP5;

	buttonArray = new CButtonArray(4, buttonPorts, mcp23008);
}

void setup()
{
	str = (char *)malloc(512);
	memset(str, 0, 512);

	/* connect u8glib with m2tklib */
	m2_SetU8g(u8g.getU8g(), m2_u8g_box_icon);

	/* assign u8g font to index 0 */
	m2.setFont(0, u8g_font_7x13);

	pictureLoop(false);

	initializeHW();

	m2.setRoot(&top_el_vlist);	
}

// the loop routine runs over and over again forever:
void loop()
{
	//Log("Main loop Distance: %d\n", mb1040->ReadSensor());
	//Log("Garage door sensor array state: %d\n", doorSensorArray->GetDoorState());

	//relay->openRelayChannel(0);
	//relay->closeRelayChannel(1);
	//delay(2000);
	//relay->closeRelayChannel(0);
	//relay->openRelayChannel(1);

	//Log("Main loop Distance: %d\n", mb1040->ReadSensor());
	//Log("Garage door sensor array state: %d\n", doorSensorArray->GetDoorState());
	//delay(2000);

	//Log("Button 0 value: %d\n", buttonArray->readButton(0));
	//delay(1000);

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

