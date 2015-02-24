#pragma once
#include "M2tk.h"
#include "m2ghu8g.h"
#include "U8glib.h"
#include "Bitmaps.h"

// Main UI variables
extern U8GLIB_LM6059 u8g;
extern M2tk m2;

// UI Functions
extern void fn_display_distance(m2_el_fnarg_p fnarg);
extern void fn_display_door_state(m2_el_fnarg_p fnarg);
extern void fn_open_close_door(m2_el_fnarg_p fnarg);
extern void fn_distance_ok(m2_el_fnarg_p fnarg); 
extern void fn_door_state_ok(m2_el_fnarg_p fnarg);
extern void draw();
extern "C" uint8_t m2_es_i2c(m2_p ep, uint8_t msg);
extern void pictureLoop(bool checkKeys = true);
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

// UI Screen Variables
extern uint32_t number;
extern char	*str;
extern uint8_t state;

// Start-up Screen
M2_LABEL(init_label, "x0y0", "Initializing...");
M2_XBMLABELP(init_image, "x0y0", 128, 64, (char *)image_data_GarageDoor);
M2_LIST(init_list) = { &init_image, &init_label };
M2_XYLIST(init_vlist, NULL, init_list);

// Main test UI
M2_BUTTON(el_display_distance, "", "Display Distance", fn_display_distance);
M2_BUTTON(el_display_door_state, "", "Display Door State", fn_display_door_state);
M2_BUTTON(el_open_close_door, "", "Open/Close Door", fn_open_close_door);
M2_LIST(list) = { &el_display_distance, &el_display_door_state, &el_open_close_door };
M2_VLIST(top_el_vlist, NULL, list);

// Distance Test UI
M2_LABEL(distance_label, NULL, "Distance: ");
M2_LABELPTR(distance_value, NULL, (const char**)(&str));
M2_LIST(distancelist) = { &distance_label, &distance_value };
M2_HLIST(distance_hlist, NULL, distancelist);
M2_BUTTON(distance_button, NULL, "OK", fn_distance_ok);
M2_LIST(distance_toplist) = { &distance_hlist, &distance_button };
M2_VLIST(distance_vlist, NULL, distance_toplist);

// Door State Test UI
M2_LABEL(door_state_label, NULL, "Door State: ");
M2_LABELPTR(door_state_value, NULL, (const char**)(&str));
M2_LIST(door_statelist) = { &door_state_label, &door_state_value };
M2_HLIST(door_state_hlist, NULL, door_statelist);
M2_BUTTON(door_state_ok_button, NULL, "OK", fn_door_state_ok);
M2_LIST(door_state_toplist) = { &door_state_hlist, &door_state_ok_button };
M2_VLIST(door_state_vlist, NULL, door_state_toplist);