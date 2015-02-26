#include "stdafx.h"
#include "Button.h"

// Individual button class for an I2C button
// Actual button in the test system is a http://www.amazon.com/gp/product/B008DS1GY0/ref=oh_aui_search_detailpage?ie=UTF8&psc=1

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