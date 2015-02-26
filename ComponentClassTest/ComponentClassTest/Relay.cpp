#include "stdafx.h"
#include "Relay.h"

// Relay class for the I2C connected relay
// Actual device is a SainSmart 2 channel relay module http://www.amazon.com/SainSmart-2-CH-2-Channel-Relay-Module/dp/B0057OC6D8

CRelay::CRelay(int numberChannels, CI2CPortExpander::I2CExpPorts relayPorts[], int powerPin, CI2CPortExpander* portExpander)
{
	m_portExpander = portExpander;

	for (int i = 0; i < numberChannels; i++)
	{
		m_relayPorts.push_back(std::make_unique<CI2CPortExpander::I2CExpPorts>(relayPorts[i]));

		// Configure the port expander to use the port as output
		portExpander->setIODIR(relayPorts[i], CI2CPortExpander::I2CExpIODirection::Output, true);
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

// TODO: Add a function to define if the channel is normally open or normally closed to support pulsing.

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
	m_portExpander->writeGPIO(*m_relayPorts[relayChannel], (CI2CPortExpander::I2CExpGPIOValue)RELAY_OPEN, true);
}

// Causes the relay to close the specified contact
void CRelay::closeRelayChannel(int relayChannel)
{
	m_portExpander->writeGPIO(*m_relayPorts[relayChannel], (CI2CPortExpander::I2CExpGPIOValue)RELAY_CLOSED, true);
}

void CRelay::pulseRelayChannel(int relayChannel, int msPulse)
{
	// TODO: Handle the NC/NO state of the relay channel

	openRelayChannel(relayChannel);

	delay(msPulse);

	closeRelayChannel(relayChannel);
}