#include "UltrasonicSensor.h"


CUltrasonicSensor::CUltrasonicSensor(int powerPin, int readPin)
{
	Log("Creating Ultrasonic Sensor Object\n");

	m_SensorPowerPin = powerPin;
	m_SensorReadPin = readPin;
	m_SensorUpTime = millis();

	pinMode(powerPin, OUTPUT);
	pinMode(readPin, INPUT);

	// Start the serial access for the MB1040
	Serial.begin(CBR_9600, Serial.SERIAL_8N1);

	TurnSensorOn();

	WaitForValidSensorData();

	Log("ultrasonic Sensor created\n");
}


CUltrasonicSensor::~CUltrasonicSensor()
{
}

void CUltrasonicSensor::TurnSensorOn()
{
	Log("Turning Ultrasonic Sensor on\n");

	digitalWrite(m_SensorPowerPin, SENSOR_ON);

	// Delay to ensure that the sensor is initialized and stable
	delay(100);
}

void CUltrasonicSensor::TurnSensorOff()
{
	Log("Turning Ultrasonic Sensor off\n");

	digitalWrite(m_SensorPowerPin, SENSOR_OFF);
}

// Reads the current sensor value
int CUltrasonicSensor::ReadSensor()
{
	char serialData = 0;
	char stringDistance[3];
	int distance = 0;

	Log("Reading Ultrasonic Sensor\n");

	memset(stringDistance, 0, sizeof(stringDistance));

	// TODO: Need to work with the sensor to keep the reading current otherwise a single call to 
	// this function will only read the first reading in the buffer

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
	Log("Sensor distance read: %d\n", distance);

	// Return the distance or zero if there was some problem reading
	return distance;
}

// This function throws away the sensor start-up information
void CUltrasonicSensor::WaitForValidSensorData()
{
	char serialString[5];
	bool bValidReading = false;

	Log("Waiting for valid Ultrasonic Sensor data\n");

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

	Log("Receiving valid Ultrasonic Sensor data\n");
}