#include "ButtonArray.h"
#include <memory>


CButtonArray::CButtonArray(int numberButtons, CI2CPortExpander::I2CExpPorts buttonPorts[], CI2CPortExpander* portExpander)
{
	m_portExpander = portExpander;

	m_buttons = std::make_unique<CButton*[]>(numberButtons);

	for (int i = 0; i < numberButtons; i++)
	{
		m_buttons[i] = new CButton(buttonPorts[i], portExpander);
	}
}

CButtonArray::~CButtonArray()
{
}

CButton::ButtonState CButtonArray::readButton(int buttonNumber)
{
	return m_buttons[buttonNumber]->readButton();
}