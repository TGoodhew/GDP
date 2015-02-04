#pragma once
#include "stdafx.h"
#include "arduino.h"
#include "wire.h"

// Base address of device
#define MCP23008_BASE_ADDRESS 0x20

class CI2CPortExpander
{
public:
	// GPIO ports
	enum class I2CExpPorts
	{
		PORT_GP0,
		PORT_GP1,
		PORT_GP2,
		PORT_GP3,
		PORT_GP4,
		PORT_GP5,
		PORT_GP6,
		PORT_GP7
	};

	//IODIR direction
	enum class I2CExpIODirection
	{
		Output = 0,
		Input = 1
	};

	//IOPOL polarity
	enum class I2CExpIOPolarity
	{
		Same = 0,
		Opposite = 1
	};

	//GPINTEN enable interrupt
	enum class I2CExpGPINTEnable
	{
		Disable = 0,
		Enable = 1
	};

	//DEFVAL camparison value
	enum class I2CExpDEFVALComparison
	{
		Low = 0,
		High = 1
	};

	//INTCON comparison control
	enum class I2CExpINTCONControl
	{
		Previous = 0,
		DEFVALRegister = 1
	};

	//IOCON bit value
	enum class I2CExpIOCONValue
	{
		Low = 0,
		High = 1
	};

	//GPPU enable
	enum class I2CExpGPPUEnable
	{
		Disabled = 0,
		Enabled = 1
	};

	//INTF condition
	enum class I2CExpINTFCondition
	{
		NoInterrupt = 0,
		Interrupt = 1
	};

	//INTCAP value
	enum class I2CExpINTCAPValue
	{
		Low = 0,
		High = 1
	};

	//GPIO Value
	enum class I2CExpGPIOValue
	{
		Low = 0,
		High = 1
	};

	//OLAT Value
	enum class I2CExpOLATValue
	{
		Low = 0,
		High = 1
	};

	// Register bit
	enum class I2CExpRegisterBit
	{
		low = 0,
		High = 1
	};

private:
	// Registers
	enum class I2CExpRegisters
	{
		MCP23008_IODIR = 0x00,
		MCP23008_IPOL = 0x01,
		MCP23008_GPINTEN = 0x02,
		MCP23008_DEFVAL = 0x03,
		MCP23008_INTCON = 0x04,
		MCP23008_IOCON = 0x05,
		MCP23008_GPPU = 0x06,
		MCP23008_INTF = 0x07,
		MCP23008_INTCAP = 0x08,
		MCP23008_GPIO = 0x09,
		MCP23008_OLAT = 0x0A
	};

	// GPIO Port Bits
	enum class I2CExpPortBits
	{
		PORT_GP0_BIT = (1u << 0),
		PORT_GP1_BIT = (1u << 1),
		PORT_GP2_BIT = (1u << 2),
		PORT_GP3_BIT = (1u << 3),
		PORT_GP4_BIT = (1u << 4),
		PORT_GP5_BIT = (1u << 5),
		PORT_GP6_BIT = (1u << 6),
		PORT_GP7_BIT = (1u << 7)
	};

	byte m_address = 0x20; // the address of the MCP23008 - According to datasheet it can range from 0x20 to 0x27
	byte m_iodirSetting = 255; // set values for IODIR via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	byte m_iopolSetting = 0; // set values for IOPOL via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	byte m_gpintenSetting = 0; // set values for GPINTEN via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	byte m_defvalSetting = 0; // set values for DEFVAL via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	byte m_intconSetting = 0; // set values for INTCON via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	byte m_ioconSetting = 0; // set values for IOCON via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	byte m_gppuSetting = 0; // set values for GPPU via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	byte m_intfSetting = 0; // contains values for INTF - Cleared on read of INTCAP or GPIO
	byte m_intcapValue = 0; // contains values for INCAP - Cleared on read
	byte m_gpioValue = 0; // set values for GPIO via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	byte m_olatSetting = 0; // set values for OLAT via |= PortBits::PORT_GP0_BIT or clear via &= ~PortBits::PORT_GP0_BIT
	void writeRegister(I2CExpRegisters targetRegister, byte outValue);
	byte CI2CPortExpander::readRegister(I2CExpRegisters targetRegister);
	void setPortBit(I2CExpPorts targetPort, I2CExpRegisterBit regBit, byte* m_pRegByte);
public:
	CI2CPortExpander(); // Default I2C address of 0x20 - See datasheet 1.4 Hardware Address Decoder
	CI2CPortExpander(byte i2cAddress); // User specified address - See datasheet 1.4 Hardware Address Decoder
	~CI2CPortExpander();
	// This function sets the IO direction for GPIO
	void setIODIR(I2CExpPorts targetPort, I2CExpIODirection ioDir, bool updateFlag);
	// Configure the input olarity on GPIO registers
	void setIPOL(I2CExpPorts targetPort, I2CExpIOPolarity iPol, bool updateFlag);
	// Sets the IOCON register value
	void setIOCON(I2CExpPorts targetPort, I2CExpIOCONValue ioCon, bool updateFlag);
	// Configures the pullup resistors for GPIO
	void setGPPU(I2CExpPorts targetPort, I2CExpGPPUEnable gppuEnable, bool updateFlag);
	// Writes to the GPIO register
	void writeGPIO(I2CExpPorts targetPort, I2CExpGPIOValue gpioValue, bool updateFlag);
	// Reads the GPIO register
	byte readGPIO();
	// Sets the GPINTEN register value
	I2CExpGPIOValue readGPIOPort(I2CExpPorts readPort);
	void setGPINTEN(I2CExpPorts targetPort, I2CExpGPINTEnable gpintEnable, bool updateFlag);
	// Sets the DEFVAL register value
	void setDEFVAL(I2CExpPorts targetPort, I2CExpDEFVALComparison defValue, bool updateFlag);
	// Sets the INTCON register value
	void setINTCON(I2CExpPorts targetPort, I2CExpINTCONControl intControl, bool updateFlag);
	// read the value of the INTF register
	byte readINTF();
	// read the value of the INTCAP register
	byte readINTCAP();
	// read the value of the OLAT register
	byte readOLAT();
	// write to the OLAT register
	void writeOLAT(I2CExpPorts targetPort, I2CExpOLATValue olatValue, bool updateFlag);
};

