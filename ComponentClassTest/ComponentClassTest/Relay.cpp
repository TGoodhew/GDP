#include "Relay.h"


CRelay::CRelay(int numberChannels, int relayPins[], int powerPin)
{
	// Create a private array of the 
	m_RelayControlPins = new int[numberChannels];

	// Copy the relayPins array and set the pin as OUTPUT
	for (int i = 0; i < numberChannels; i++)
	{
		m_RelayControlPins[i] = relayPins[i];
		pinMode(m_RelayControlPins[i], OUTPUT);
	}

	// Store the power control pin
	m_RelayPowerPin = powerPin;

	// Set the power pin to OUTPUT
	pinMode(m_RelayPowerPin, OUTPUT);

	// Turn the relay on
	digitalWrite(m_RelayPowerPin, RELAY_ON);
}


CRelay::~CRelay()
{
}

// Turns the relay board on
void CRelay::turnRelayOn()
{
	digitalWrite(m_RelayPowerPin, RELAY_ON);
}

// Turns the relay board off
void CRelay::turnRelayOff()
{
	digitalWrite(m_RelayPowerPin, RELAY_OFF);
}

// Causes the relay to open the specified contact
void CRelay::openRelayChannel(int relayChannel)
{
	// Decrement the relay channel number to be an array index
	digitalWrite(m_RelayControlPins[relayChannel - 1], RELAY_OPEN);
}

// Causes the relay to close the specified contact
void CRelay::closeRelayChannel(int relayChannel)
{
	// Decrement the relay channel number to be an array index
	digitalWrite(m_RelayControlPins[relayChannel - 1], RELAY_CLOSED);
}