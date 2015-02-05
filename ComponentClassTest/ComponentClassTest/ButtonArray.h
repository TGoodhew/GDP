#pragma once
#include "Button.h"
#include "I2CPortExpander.h"
#include "Button.h"
#include <memory>

class CButtonArray
{
private:
	CI2CPortExpander* m_portExpander = nullptr;
	std::unique_ptr <CButton*[]> m_buttons = nullptr;

public:
	CButtonArray(int numberButtons, CI2CPortExpander::I2CExpPorts buttonPorts[], CI2CPortExpander* portExpander);
	~CButtonArray();
	CButton::ButtonState readButton(int buttonNumber);

};

