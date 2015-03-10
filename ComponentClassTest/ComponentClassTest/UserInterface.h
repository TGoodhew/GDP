#pragma once
#include "M2tk.h"
#include "m2ghu8g.h"
#include "U8glib.h"
#include "Bitmaps.h"

// Main UI variables
extern U8GLIB_LM6059 u8g;
extern M2tk m2;

// UI Functions
// Buttons
extern void fn_display_distance(m2_el_fnarg_p fnarg);
extern void fn_display_door_state(m2_el_fnarg_p fnarg);
extern void fn_open_close_door(m2_el_fnarg_p fnarg);
extern void fn_distance_ok(m2_el_fnarg_p fnarg); 
extern void fn_door_state_ok(m2_el_fnarg_p fnarg);

// M2tklib implementation functions
// Event Source - interfaces the buttons to the UI elements by create KEY messages
extern "C" uint8_t m2_es_i2c(m2_p ep, uint8_t msg);
// Picture Loop - calls m2tklib library functions to draw the UI elements and checks for input
extern void pictureLoop(bool checkKeys = true);

// State machine implementation
extern void set_next_state();

// Define state machine
#define STATE_DISPLAY_MAIN_MENU 1
#define STATE_WAIT_MAIN_MENU 2
#define STATE_DISPLAY_DISTANCE 3
#define STATE_WAIT_DISTANCE 4
#define STATE_GET_DISTANCE 5
#define STATE_DISPLAY_DOOR_STATE 6
#define STATE_WAIT_DOOR_STATE 7
#define STATE_GET_DOOR_STATE 8
#define STATE_OPEN_CLOSE_DOOR 9

/*
Main UI definitions
*/

// UI Variables
extern char	*str;
extern int stateMachineState;

// Start-up Screen
M2_LABEL(el_init_label, "x0y0", "Initializing...");
M2_XBMLABELP(el_init_image, "x0y0", 128, 64, (char *)image_data_GarageDoor);
M2_LIST(el_init_list) = { &el_init_image, &el_init_label };
M2_XYLIST(el_init_vlist, NULL, el_init_list);

// Main test UI
M2_BUTTON(el_display_distance, "", "Display Distance", fn_display_distance);
M2_BUTTON(el_display_door_state, "", "Display Door State", fn_display_door_state);
M2_BUTTON(el_open_close_door, "", "Open/Close Door", fn_open_close_door);
M2_LIST(el_main_list) = { &el_display_distance, &el_display_door_state, &el_open_close_door };
M2_VLIST(el_main_vlist, NULL, el_main_list);

// Distance Test UI
M2_LABEL(el_distance_label, NULL, "Distance: ");
M2_LABELPTR(el_distance_value, NULL, (const char**)(&str));
M2_LIST(el_distance_label_list) = { &el_distance_label, &el_distance_value };
M2_HLIST(el_distance_hlist, NULL, el_distance_label_list);
M2_BUTTON(el_distance_button, NULL, "OK", fn_distance_ok);
M2_LIST(el_distance_list) = { &el_distance_hlist, &el_distance_button };
M2_VLIST(el_distance_vlist, NULL, el_distance_list);

// Door State Test UI
M2_LABEL(el_door_state_label, NULL, "Door State: ");
M2_LABELPTR(el_door_state_value_label, NULL, (const char**)(&str));
M2_LIST(el_door_state_display_list) = { &el_door_state_label, &el_door_state_value_label };
M2_HLIST(el_door_state_hlist, NULL, el_door_state_display_list);
M2_BUTTON(el_door_state_ok_button, NULL, "OK", fn_door_state_ok);
M2_LIST(el_door_state_list) = { &el_door_state_hlist, &el_door_state_ok_button };
M2_VLIST(el_door_state_vlist, NULL, el_door_state_list);