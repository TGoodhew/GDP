#pragma once
#include "stdafx.h"
#include "arduino.h"

#define RELAY_ON		HIGH
#define RELAY_OFF		LOW
#define RELAY_OPEN		HIGH
#define	RELAY_CLOSED	LOW

class CRelay
{
public:
	CRelay(int numberChannels, int relayPins[], int powerPin);
	~CRelay();
private:
	int *m_RelayControlPins;
	bool m_RelayPower;
	int m_RelayPowerPin;
public:

	// Turns the relay board on
	void turnRelayOn();
	// Turns the relay board off
	void turnRelayOff();
	// Causes the relay to open the specified contact
	void openRelayChannel(int relayChannel);
	// Causes the relay to close the specified contact
	void closeRelayChannel(int relayChannel);
};

