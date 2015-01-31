#include "UltrasonicSensor.h"

// CUltrasonicSensor - This class wraps access to the MB1040 ultrasonic sensor
//
// To use you create an instance of the object in the Setup method of your app. As this class
// uses the Arduino HarwareSerial class the sketch environment must be setup before you instantiate
// the object.
//

/// <summary>
/// The constructor will store the power and control pins in the class instance and set them up for OUTPUT. It then turns on Hardware Serial for port 1
/// and starts the sensor boot process. The sensor emits a copyright string that will be read in and discarded by WaitForValidSensorData().
/// Once valid data is received the sensor will stop ranging and the serial buffer cleared.
/// </summary>
/// <param name="powerPin">The pin number that controls the power to the sensor.</param>
/// <param name="controlPin">The pin number that controls when to take a reading. The MB1040 will continually measure range and output if RX data (Pin 4) is left unconnected or held high. If held low the sensor will stop ranging. Bring RX (Pin 4) high for 20uS or more to command a range reading.</param>
CUltrasonicSensor::CUltrasonicSensor(int powerPin, int controlPin)
{
	Log("Creating Ultrasonic Sensor Object\n");

	m_SensorPowerPin = powerPin;
	m_SensorControlPin = controlPin;
	m_SensorUpTime = millis();

	pinMode(powerPin, OUTPUT);
	pinMode(controlPin, OUTPUT);

	// Start the serial access for the MB1040
	Serial.begin(CBR_9600, Serial.SERIAL_8N1);

	ResetSensor();

	Log("ultrasonic Sensor created\n");
}


CUltrasonicSensor::~CUltrasonicSensor()
{
}

void CUltrasonicSensor::StartRanging()
{
	// Starts the sensor ranging
	digitalWrite(m_SensorControlPin, HIGH);
}

void CUltrasonicSensor::StopRanging()
{
	// Stops the sensor ranging
	digitalWrite(m_SensorControlPin, LOW);
}

void CUltrasonicSensor::TakeReading()
{
	StartRanging();

	delayMicroseconds(20);

	StopRanging();
}

/// <summary>
/// TurnSensorOn sets the defined power pin to the value os SENSOR_ON and then calls WaitForValidSensorData() to wait for valid data to arrive.
/// </summary>
void CUltrasonicSensor::TurnSensorOn()
{
	Log("Turning Ultrasonic Sensor on\n");

	digitalWrite(m_SensorPowerPin, SENSOR_ON);

	WaitForValidSensorData();

}

void CUltrasonicSensor::TurnSensorOff()
{
	Log("Turning Ultrasonic Sensor off\n");

	digitalWrite(m_SensorPowerPin, SENSOR_OFF);

	// Delay to ensure clean shutdown
	delay(10);

	// Clear the serial buffer
	ClearSerialRXBuffer();

	// Reset the valid data flag so that the copyright string will be removed on next power on
	m_ReceivingValidData = false;
}

void CUltrasonicSensor::ResetSensor()
{
	Log("Resetting Ultrasonic Sensor\n");

	TurnSensorOff();

	TurnSensorOn();
}

// Reads the current sensor value
int CUltrasonicSensor::ReadSensor()
{
	char serialData = 0;
	char stringDistance[3];
	int distance = 0;

	Log("Reading Ultrasonic Sensor\n");

	// Tell the sensor to take a reading
	TakeReading();

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
	Log("Sensor data available: %d\n", Serial.available());
	// Return the distance or zero if there was some problem reading
	return distance;
}

// This function throws away the sensor start-up information
void CUltrasonicSensor::WaitForValidSensorData()
{
	char serialString[6];
	bool bValidReading = false;

	if (!m_ReceivingValidData)
	{
		Log("Waiting for valid Ultrasonic Sensor data\n");

		StartRanging();

		memset(serialString, 0, sizeof(serialString));

		while (!bValidReading)
		{
			// Keep throwing away characters until we get what could be the start of a reading
			while (Serial.peek() != 'R')
				Serial.read();

			// Read the next 5 characters to see if they're a distance reading
			for (int count = 0; count < 5; count++)
				serialString[count] = Serial.read();

			Log("String read: %s\n", serialString);

			// Check to see if they match the pattern
			if ((serialString[0] == 'R') &
				((serialString[1] > 47) & (serialString[1] < 58)) &
				((serialString[2] > 47) & (serialString[2] < 58)) &
				((serialString[3] > 47) & (serialString[3] < 58)) &
				(serialString[4] == 13))
			{
				bValidReading = true;
				Log("Valid Reading\n");
			}
			else
				Log("Invalid Reading\n");

		}

		StopRanging();

		// Delay 50ms to ensure that the last read has been transmitted
		delay(50);

		// Clear the serial buffer
		ClearSerialRXBuffer();

		// indicate that we have received valid data
		m_ReceivingValidData = true;

		Log("Receiving valid Ultrasonic Sensor data\n");
	}
}

void CUltrasonicSensor::ClearSerialRXBuffer()
{
	while (Serial.available() > 0)
		Serial.read();
}