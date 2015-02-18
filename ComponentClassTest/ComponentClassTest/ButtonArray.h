#pragma once
#include "Button.h"
#include "I2CPortExpander.h"
#include "Button.h"
#include <memory>
#include <vector>

class CButtonArray
{
private:
	CI2CPortExpander* m_portExpander = nullptr;
	std::vector<std::unique_ptr<CButton>> m_buttons;

public:
	CButtonArray(int numberButtons, CI2CPortExpander::I2CExpPorts buttonPorts[], CI2CPortExpander* portExpander);
	~CButtonArray();
	CButton::ButtonState readButton(int buttonNumber);

};

