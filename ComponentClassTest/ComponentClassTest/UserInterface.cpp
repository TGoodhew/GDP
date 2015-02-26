#include "stdafx.h"
#include "UserInterface.h"
#include "CoreDevices.h"

U8GLIB_LM6059 u8g(7, 6, 9);
M2tk m2(&el_init_vlist, m2_es_i2c, m2_eh_4bs, m2_gh_u8g_bfs);

// UI Variables
char	*str;
int stateMachineState = 1;
unsigned long next_distance_check = 0;
unsigned long next_door_check = 0;
bool refresh_screen = false;

// Main UI rendering loop
void pictureLoop(bool checkKeys)
{
	if (checkKeys)
		m2.checkKey();

	if ((m2.handleKey() != 0) || (refresh_screen))
	{
		refresh_screen = 0;
		u8g.firstPage();
		do 
		{
			if (checkKeys)
				m2.checkKey();

			m2.draw();

		}
		while (u8g.nextPage());
	}

	set_next_state();
}

// Button functions
void fn_display_distance(m2_el_fnarg_p fnarg)
{
	stateMachineState = STATE_DISPLAY_DISTANCE;
}

void fn_display_door_state(m2_el_fnarg_p fnarg)
{
	stateMachineState = STATE_DISPLAY_DOOR_STATE;
}

void fn_open_close_door(m2_el_fnarg_p fnarg)
{
	stateMachineState = STATE_OPEN_CLOSE_DOOR;
}

void fn_distance_ok(m2_el_fnarg_p fnarg)
{
	stateMachineState = STATE_DISPLAY_MAIN_MENU;
}

void fn_door_state_ok(m2_el_fnarg_p fnarg)
{
	stateMachineState = STATE_DISPLAY_MAIN_MENU;
}

// State machine implementation
void set_next_state()
{
	// TODO: Will need to work on UI performance
	switch (stateMachineState)
	{
	case STATE_DISPLAY_MAIN_MENU:
		m2.setRoot(&el_main_vlist);
		stateMachineState = STATE_WAIT_MAIN_MENU;
		break;
	case STATE_WAIT_MAIN_MENU:
		break;
	case STATE_DISPLAY_DISTANCE:
		m2.setRoot(&el_distance_vlist);
		stateMachineState = STATE_WAIT_DISTANCE;
		break;
	case STATE_WAIT_DISTANCE:
		if (next_distance_check < millis())
			stateMachineState = STATE_GET_DISTANCE;
		break;
	case STATE_GET_DISTANCE:
		sprintf(str, "%d", mb1040->ReadSensor());
		next_distance_check = millis() + 1000;
		stateMachineState = STATE_WAIT_DISTANCE;
		refresh_screen = true;
		break;
	case STATE_DISPLAY_DOOR_STATE:
		m2.setRoot(&el_door_state_vlist);
		stateMachineState = STATE_WAIT_DOOR_STATE;
		break;
	case STATE_WAIT_DOOR_STATE:
		if (next_door_check < millis())
			stateMachineState = STATE_GET_DOOR_STATE;
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
		stateMachineState = STATE_WAIT_DOOR_STATE;
		refresh_screen = true;
		break;
	case STATE_OPEN_CLOSE_DOOR:
		relay->pulseRelayChannel(0);
		stateMachineState = STATE_WAIT_MAIN_MENU;
		break;
	}
}