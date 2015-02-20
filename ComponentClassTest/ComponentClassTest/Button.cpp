#include "stdafx.h"
#include "Button.h"


CButton::CButton(CI2CPortExpander::I2CExpPorts buttonPort, CI2CPortExpander* portExpander)
{
	m_buttonPort = buttonPort;

	m_portExpander = portExpander;

	// Set the Port expander IODIR
	m_portExpander->setIODIR(m_buttonPort, CI2CPortExpander::I2CExpIODirection::Input, true);
}

CButton::~CButton()
{
}

CButton::ButtonState CButton::readButton()
{
	return (CButton::ButtonState)m_portExpander->readGPIOPort(m_buttonPort);
}