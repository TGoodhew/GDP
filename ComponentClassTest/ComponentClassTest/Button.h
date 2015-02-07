#pragma once
#include "I2CPortExpander.h"

class CButton
{
public:
	enum class ButtonState
	{
		Open,
		Closed
	};

	CButton(CI2CPortExpander::I2CExpPorts buttonPort, CI2CPortExpander* portExpander);
	~CButton();

private:
	CI2CPortExpander::I2CExpPorts m_buttonPort;
	CI2CPortExpander* m_portExpander = nullptr;

public:
	ButtonState readButton();
};

