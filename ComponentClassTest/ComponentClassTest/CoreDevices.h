#pragma once

// Core device headers
#include "I2CPortExpander.h"
#include "GarageDoorSenorArray.h"
#include "UltrasonicSensor.h"
#include "Relay.h"
#include "DoorSensor.h"
#include "ButtonArray.h"

//// Core device globals
extern CUltrasonicSensor* mb1040;
extern CI2CPortExpander* mcp23008;
extern CRelay* relay;
extern CDoorSensor* doorSensor;
extern CGarageDoorSenorArray* doorSensorArray;
extern CButtonArray* buttonArray;