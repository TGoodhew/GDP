#include "stdafx.h"
#include "UserInterface.h"
#include "CoreDevices.h"

U8GLIB_LM6059 u8g(7, 6, 9);
M2tk m2(&init_vlist, m2_es_i2c, m2_eh_4bs, m2_gh_u8g_bfs);

// UI Variables
uint32_t number = 1234;
char	*str;
uint8_t state = 1;
uint8_t next_distance_check = 0;
uint8_t next_door_check = 0;
bool refresh_screen = false;

void fn_display_distance(m2_el_fnarg_p fnarg)
{
	state = STATE_DISPLAY_DISTANCE;
}

void fn_display_door_state(m2_el_fnarg_p fnarg)
{
	state = STATE_DISPLAY_DOOR_STATE;
}

void fn_open_close_door(m2_el_fnarg_p fnarg)
{
	state = STATE_OPEN_CLOSE_DOOR;
}

void fn_distance_ok(m2_el_fnarg_p fnarg)
{
	state = STATE_DISPLAY_MAIN_MENU;
}

void fn_door_state_ok(m2_el_fnarg_p fnarg)
{
	state = STATE_DISPLAY_MAIN_MENU;
}

void draw()
{
	m2.draw();
}

void pictureLoop(bool checkKeys)
{
	if (checkKeys)
		m2.checkKey();

	if ((m2.handleKey() != 0) || (refresh_screen))
	{
		refresh_screen = 0;
		u8g.firstPage();
		do {
			if (checkKeys)
				m2.checkKey();
			draw();
		} while (u8g.nextPage());
	}

	set_next_state();
}

void set_next_state()
{
	// TODO: Will need to work on UI performance
	switch (state)
	{
	case STATE_DISPLAY_MAIN_MENU:
		m2.setRoot(&top_el_vlist);
		state = STATE_WAIT_MAIN_MENU;
		break;
	case STATE_WAIT_MAIN_MENU:
		break;
	case STATE_DISPLAY_DISTANCE:
		m2.setRoot(&distance_vlist);
		state = STATE_WAIT_DISTANCE;
		break;
	case STATE_WAIT_DISTANCE:
		if (next_distance_check < millis())
			state = STATE_GET_DISTANCE;
		break;
	case STATE_GET_DISTANCE:
		sprintf(str, "%d", mb1040->ReadSensor());
		next_distance_check = millis() + 1000;
		state = STATE_WAIT_DISTANCE;
		refresh_screen = true;
		break;
	case STATE_DISPLAY_DOOR_STATE:
		m2.setRoot(&door_state_vlist);
		state = STATE_WAIT_DOOR_STATE;
		break;
	case STATE_WAIT_DOOR_STATE:
		if (next_door_check < millis())
			state = STATE_GET_DOOR_STATE;
		break;
	case STATE_GET_DOOR_STATE:
		switch (doorSensorArray->GetDoorState())
		{
		case DoorState::DoorClosed:
			sprintf(str, "%s", "Closed");
			break;
		case DoorState::DoorOpen:
			sprintf(str, "%s", "Open");
			break;
		case DoorState::DoorTravelling:
			sprintf(str, "%s", "Travelling");
			break;
		}
		next_door_check = millis() + 500;
		state = STATE_WAIT_DOOR_STATE;
		refresh_screen = true;
		break;
	case STATE_OPEN_CLOSE_DOOR:
		relay->pulseRelayChannel(0);
		state = STATE_WAIT_MAIN_MENU;
		break;
	}
}