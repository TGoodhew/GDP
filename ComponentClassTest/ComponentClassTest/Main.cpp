// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "GarageDoorSenorArray.h"
#include "UltrasonicSensor.h"
#include "I2CPortExpander.h"
#include "Relay.h"
#include "DoorSensor.h"
#include "ButtonArray.h"
#include <ctime>
#include "..\..\M2tklib\M2tk.h"
#include "..\..\M2tklib\utility\m2ghu8g.h"
#include "..\..\U8glib\U8glib.h"

extern "C" uint8_t m2_es_i2c(m2_p ep, uint8_t msg);

CUltrasonicSensor* mb1040;
CI2CPortExpander* mcp23008;
CRelay* relay;
CDoorSensor* doorSensor;
CGarageDoorSenorArray* doorSensorArray;
CButtonArray* buttonArray;

uint32_t number = 1234;
char	*str;
U8GLIB_LM6059 u8g(8, 10, 9);

void fn_ok(m2_el_fnarg_p fnarg) {
	/* do something with the number */
	sprintf(str, "Selected %d", number);
}

M2_LABELPTR(el_selected, NULL, (const char**)(&str));
M2_LABEL(el_label, NULL, "Num: ");
M2_U32NUM(el_num, "a1c4", &number);
M2_BUTTON(el_ok, "", " ok ", fn_ok);
M2_LIST(list) = { &el_label, &el_num, &el_ok };
M2_HLIST(el_hlist, NULL, list);
M2_LIST(toplist) = { &el_selected, &el_hlist };
M2_VLIST(top_el_vlist, NULL, toplist);

M2tk m2(&top_el_vlist, m2_es_i2c, m2_eh_4bs, m2_gh_u8g_bfs);

void draw(void) {
	m2.draw();
}

int _tmain(int argc, _TCHAR* argv[])
{
	// BUG: Need to remove this for proper use


    return RunArduinoSketch();
}

void setup()
{
	str = (char *)malloc(512);
	memset(str, 0, 512);

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

	/* connect u8glib with m2tklib */
	m2_SetU8g(u8g.getU8g(), m2_u8g_box_icon);

	/* assign u8g font to index 0 */
	m2.setFont(0, u8g_font_7x13);

}

// the loop routine runs over and over again forever:
void loop()
{
	//std::time_t t = std::time(nullptr);
	//Log("Start Loop Time: %s\n", std::asctime(std::localtime(&t)));
	//Log("Main loop Distance: %d\n", mb1040->ReadSensor());
	//Log("Garage door sensor array state: %d\n", doorSensorArray->GetDoorState());
	//relay->openRelayChannel(0);
	//relay->closeRelayChannel(1);
	//delay(2000);
	//relay->closeRelayChannel(0);
	//relay->openRelayChannel(1);
	//Log("Main loop Distance: %d\n", mb1040->ReadSensor());
	//Log("Garage door sensor array state: %d\n", doorSensorArray->GetDoorState());
	//t = std::time(nullptr);
	//Log("End Loop Time: %s\n", std::asctime(std::localtime(&t)));
	//delay(2000);

	//Log("Button 0 value: %d\n", buttonArray->readButton(0));
	//delay(1000);

	m2.checkKey();
	if (m2.handleKey() != 0)
	{
		u8g.firstPage();
		do {
			m2.checkKey();
			draw();
		} while (u8g.nextPage());
	}
}

// TODO: Need to create the m2tklib event source for the I2C port exapnder connected devices.
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

