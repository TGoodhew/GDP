#include "ButtonArray.h"

CButtonArray::CButtonArray(int numberButtons, CI2CPortExpander::I2CExpPorts buttonPorts[], CI2CPortExpander* portExpander)
{
	m_portExpander = portExpander;

	for (int i = 0; i < numberButtons; i++)
	{
		m_buttons.push_back(std::make_unique<CButton>(buttonPorts[i], portExpander));
	}
}

CButtonArray::~CButtonArray()
{
}

CButton::ButtonState CButtonArray::readButton(int buttonNumber)
{
	return m_buttons[buttonNumber]->readButton();
}