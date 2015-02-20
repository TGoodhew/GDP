#pragma once
#include "I2CPortExpander.h"
#include <memory>
#include <vector>

#define RELAY_ON		HIGH
#define RELAY_OFF		LOW
#define RELAY_OPEN		HIGH
#define	RELAY_CLOSED	LOW

class CRelay
{
public:
	CRelay(int numberChannels, CI2CPortExpander::I2CExpPorts relayPorts[], int powerPin, CI2CPortExpander* portExpander);
	~CRelay();
private:
	std::vector<std::unique_ptr<CI2CPortExpander::I2CExpPorts>> m_relayPorts;
	bool m_RelayPower;
	int m_RelayPowerPin;
	CI2CPortExpander* m_portExpander = nullptr;
public:
	// Turns the relay board on
	void turnRelayOn();
	// Turns the relay board off
	void turnRelayOff();
	// Causes the relay to open the specified contact
	void openRelayChannel(int relayChannel);
	// Causes the relay to close the specified contact
	void closeRelayChannel(int relayChannel);
	// Pulse the relay for the defined time
	void pulseRelayChannel(int relayChannel, int msPulse);
};

