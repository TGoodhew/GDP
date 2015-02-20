#pragma once

#define SENSOR_ON	LOW
#define SENSOR_OFF	HIGH

class CUltrasonicSensor
{
public:
	CUltrasonicSensor(int powerPin, int controlPin);
	~CUltrasonicSensor();
private:
	int m_SensorPowerPin;
	int m_SensorControlPin;
	unsigned long m_SensorUpTime;
	bool m_ReceivingValidData = false;
public:
	void TurnSensorOn();
	void TurnSensorOff();
	void ResetSensor();
	int ReadSensor();
private:
	// Reads the current sensor value
	// This function throws away the sensor start-up information
	void WaitForValidSensorData();
	void StartRanging();
	void StopRanging();
	void TakeReading();
	void ClearSerialRXBuffer();
};

