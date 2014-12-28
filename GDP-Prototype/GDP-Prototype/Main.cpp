// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"

// Pin assignments
#define PIN_DOOR_RELAY			2
#define PIN_CAR_PARKED			3
#define PIN_GARAGE_DOOR_OPEN	4
#define PIN_GARAGE_DOOR_CLOSED	5
#define PIN_PWR_MB1040			6
#define PIN_BUTTON_UP			8
#define PIN_BUTTON_DOWN			9
#define PIN_BUTTON_LEFT			10
#define PIN_BUTTON_RIGHT		11

// Timer definitions
#define SENSOR_RESET_TIME		900000 // Manufacture recommends a reset every 15 minutes
#define PARKED_LIGHTS_ON_TIME	60000 // Display the parked correctly lights for 60 seconds
#define DOOR_TRAVEL_TIME		30000 // This is twice the amount of time required for the door to travel a full distance
#define SENSOR_STARUP_DELAY		350 // This delay enables the sensor to power-up and take the first reading
#define SENSOR_SHUTDOWN_DELAY	50 // Give the sensor time to fully power down after it is turned off

// Timer variables
unsigned long lastSensorReset = 0;
unsigned long parkLightsOnTime = 0;
unsigned long doorTravelTimer = 0;

// State variables
bool bParkingSensorOn = false;
bool bParkingLightsOn = false;
bool bParkingInProgress = false;
bool bDoorInMotion = false;
bool bDoorOpen = false;
bool bDoorClosed = false;
bool bCarInGarage = false;
bool bCarParked = false;
bool bOkToStartParkingProcess = false;
bool bCarLeavingGarage = false;

// Prototype distance measurements
#define GARAGE_DISTANCE	40 // For the purpose of the prototype the distance from the sensor to garage door is 40 inches
#define PARKED_DISTANCE	10 // For the purpose of the prototype the distance from the sensor to a parked car is 10 inches

// Structs
typedef struct ButtonStateTag
{
	bool bUp = false;
	bool bDown = false;
	bool bLeft = false;
	bool bRight = false;
} ButtonState;

int _tmain(int argc, _TCHAR* argv[])
{
	return RunArduinoSketch();
}

void setup()
{
	// Setup the pins
	pinMode(PIN_PWR_MB1040, OUTPUT);
	pinMode(PIN_DOOR_RELAY, OUTPUT);
	pinMode(PIN_CAR_PARKED, OUTPUT);
	pinMode(PIN_GARAGE_DOOR_OPEN, INPUT);
	pinMode(PIN_GARAGE_DOOR_CLOSED, INPUT);

	digitalWrite(PIN_PWR_MB1040, LOW); // Turn power on to the MB 1040
	digitalWrite(PIN_DOOR_RELAY, LOW); // Open the relay (using LOW as the transistor ensures correct operation when Galileo is off or starting)
	digitalWrite(PIN_CAR_PARKED, LOW); // Open the relay (using LOW as the transistor ensures correct operation when Galileo is off or starting)

	// Start the serial access for the MB1040
	Serial.begin(CBR_9600, Serial.SERIAL_8N1);

	// Reset the MB1040 to ensure clean start
	ResetSensor(true);
}

// Reads the serial string from the MB1040 and converts it into an integer reflecting the distance in inches
int ReadDistance()
{
	char serialData = 0;
	char stringDistance[3];
	int distance = 0;

	memset(stringDistance, 0, sizeof(stringDistance));

	// Keep throwing away characters until we get to the start of a distance reading
	while (Serial.peek() != 'R')
		Serial.read();

	// A distance reading is now ready so let's read it
	serialData = Serial.read();

	// Make sure we're at the start of the reading
	if (serialData == 'R')
	{
		int count = 0;

		// Read the 3 character distance string
		while ((Serial.peek() != '\r') & (count < 3))
		{
			stringDistance[count++] = Serial.read();
		}

		// Convert it into a int
		distance = atoi(stringDistance);
	}

	// Log the distance to the console
	Log("%d\n", distance);

	// Return the distance or zero if there was some problem reading
	return distance;
}

// This function throws away the sensor start-up information
void WaitForValidSensorData()
{
	char serialString[5];
	bool bValidReading = false;

	memset(serialString, 0, sizeof(serialString));

	while (!bValidReading)
	{
		// Keep throwing away characters until we get what could be the start of a reading
		while (Serial.peek() != 'R')
			Serial.read();

		// Read the next 5 characters to see if they're a distance reading
		for (int count = 0; count < 5; count++)
			serialString[count] = Serial.read();

		// Check to see if they match the pattern
		if ((serialString[0] == 'R') &
			((serialString[1] > 47) & (serialString[1] < 58)) &
			((serialString[2] > 47) & (serialString[2] < 58)) &
			((serialString[3] > 47) & (serialString[3] < 58)) &
			(serialString[4] == 13))
			bValidReading = true;
	}
}

// Reset the sensor every 15 mins of runtime
void ResetSensor(bool bReset = FALSE)
{
	unsigned long timeSinceLastCheck = 0;

	// If the parking sensor isn't on then don't reset it unless this is a forced reset
	if ((!bParkingSensorOn) & (bReset == FALSE))
		return;

	// Get the time difference since the last check
	timeSinceLastCheck = millis() - lastSensorReset;

	// If the number is greater than the reset time, including the 2's complement in case of roll over
	// or we're forcing a reset with bReset == TRUE
	if ((timeSinceLastCheck > SENSOR_RESET_TIME) | (bReset == TRUE))
	{
		Log("Resetting Sensor\n");
		TurnParkingSensorOff(); // Turn the sensor off
		TurnParkingSensorOn(); // Turn the sensor on
		lastSensorReset = millis(); // Record the reset time
		Log("Sensor Reset\n");
	}

}

// Close the relay connected to the door control panel input on the garage door opener
// This connectionm is in parallel with the control in the garage as it is also just a simple switch
void ActivateDoorControl()
{
	Log("Pressing Door Button\n");

	// To activate the door we act like someone pressing the button
	digitalWrite(PIN_DOOR_RELAY, HIGH); // Take the relay control pin high to activate
	delay(500); // Keep the 'button' pressed for half a second
	digitalWrite(PIN_DOOR_RELAY, LOW); // Take the relay control low to 'release the button'

	// The door is now in motion so set the travel timer
	bDoorInMotion = true;
	doorTravelTimer = millis();

	Log("Released Door Button\n");
}

void ParkingLightsTimer()
{
	// if the timer is set to zero then the lights are off
	if (parkLightsOnTime == 0)
		return;

	// Otherwise check how long the lights have been on
	if ((millis() - parkLightsOnTime) > PARKED_LIGHTS_ON_TIME)
	{
		TurnCarParkedLightsOff();
	}
}

void TurnCarParkedLightsOn()
{
	if (!bParkingLightsOn)
	{
		bParkingInProgress = true; // We're turning off the lights so by definition parking has stopped
		digitalWrite(PIN_CAR_PARKED, LOW); // Turn the correctly parked lights off
		parkLightsOnTime = millis(); // Record the on time
		Log("Parking Lights On\n");
	}
}

void TurnCarParkedLightsOff()
{
	if (bParkingLightsOn)
	{
		bParkingInProgress = false; // We're turning off the lights so by definition parking has stopped
		digitalWrite(PIN_CAR_PARKED, LOW); // Turn the correctly parked lights off
		parkLightsOnTime = 0; // Reset the timer
		Log("Parking Lights Off\n");
	}
}

void PerformParkingProcess()
{
	// TODO: Implement the parking process
	Log(L"Parking\n");
}

// Checks the door state and updates the globals to reflect that state
void CheckDoorState()
{
	// Get the door sensor states
	bDoorClosed = digitalRead(PIN_GARAGE_DOOR_CLOSED);
	bDoorOpen = digitalRead(PIN_GARAGE_DOOR_OPEN);

	// if the door is neither open or closed then it is either in motion or stuck. In either case treat the door as in motion.
	if (!bDoorClosed & !bDoorOpen)
		bDoorInMotion = true;
	else
		bDoorInMotion = false;
}

// This function turns the MB1040 on and then waits till good distance data is coming in
void TurnParkingSensorOn()
{
	bParkingSensorOn = true;
	digitalWrite(PIN_PWR_MB1040, LOW); // Turn power on to the MB 1040
	delay(SENSOR_STARUP_DELAY); // Give the sensor time to turn on and post it's start information to the serial port
	WaitForValidSensorData(); // Wait for valid data to start arriving from the sensor
	Log(L"Parking Sensor On\n");
}

// This function turns the MB1040 off
void TurnParkingSensorOff()
{
	bParkingSensorOn = false;
	digitalWrite(PIN_PWR_MB1040, HIGH); // Turn power off to the MB 1040
	delay(SENSOR_SHUTDOWN_DELAY); // Give the sensor a chance to turn off
}

// Get all the button states
void ReadButtonState(ButtonState *buttonState)
{
	// Set all the button states to false
	buttonState->bUp = false;
	buttonState->bDown = false;
	buttonState->bLeft = false;
	buttonState->bRight = false;

	// Get the button states
	if (digitalRead(PIN_BUTTON_UP))
		buttonState->bUp = true;
	if (digitalRead(PIN_BUTTON_DOWN))
		buttonState->bDown = true;
	if (digitalRead(PIN_BUTTON_LEFT))
		buttonState->bLeft = true;
	if (digitalRead(PIN_BUTTON_RIGHT))
		buttonState->bRight = true;
}

// Checks to see if there is a car in the parked position
bool IsCarInParkedPosition()
{
	int distance = 0;

	// Read the distance
	distance = ReadDistance();

	// If the distance is less than or equal to the parking distance
	// then there is a parked car.
	if (distance <= PARKED_DISTANCE)
		return true;

	return false;
}

bool IsCarInGarage()
{
	int distance = 0;

	// Read the distance
	distance = ReadDistance();

	// If the distance is less than or equal to the garage length
	// then there is a car int he garage
	if (distance <= GARAGE_DISTANCE)
		return true;

	return false;
}
// the loop routine runs over and over again forever:
void loop()
{
	// Run the timers
	if (bParkingSensorOn)
		ResetSensor();

	if (bParkingLightsOn)
		ParkingLightsTimer();

	// TODO: Need to handle the case where the door isn't open or closed by timing the open/close process and giving an error if exceeded

	// Get the current door state
	CheckDoorState();

	// When the door is open and there is a car already at the parking distance do not display the parking lights
	// Once the car moves off the parking spot the lights should display until the car leaves the garage
	if (bDoorOpen)
	{
		// If we aren't in the parking process then workout if we should be
		if (!bOkToStartParkingProcess)
		{
			// Check to see if a car is already parked
			bCarParked = IsCarInParkedPosition();

			// If a car is parked then we need to wait for it to leave the garage before starting the parking process
			if (bCarParked)
				bOkToStartParkingProcess = false;
			else
			{
				bCarInGarage = IsCarInGarage();

				// If there isn't a car in the garage we can start the parking process
				if (!bCarInGarage)
					bOkToStartParkingProcess = true;
			}
		}
		else
		{
			// We can now perform the parking process
			PerformParkingProcess();
		}
	}

	// Once the door is closed we can turn everything off
	if (bDoorClosed)
	{
		bOkToStartParkingProcess = false;
		TurnCarParkedLightsOff();
	}
}