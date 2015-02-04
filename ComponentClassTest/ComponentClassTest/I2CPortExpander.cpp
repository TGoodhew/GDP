#include "I2CPortExpander.h"

CI2CPortExpander::CI2CPortExpander()
{
	// Wire.begin must be called prior to creating an object of this class

	// Reset the expander to default values (per datasheet section 1.6)
	writeRegister(I2CExpRegisters::MCP23008_IODIR, 255);
	writeRegister(I2CExpRegisters::MCP23008_IPOL, 0);
	writeRegister(I2CExpRegisters::MCP23008_GPINTEN, 0);
	writeRegister(I2CExpRegisters::MCP23008_DEFVAL, 0);
	writeRegister(I2CExpRegisters::MCP23008_INTCON, 0);
	writeRegister(I2CExpRegisters::MCP23008_IOCON, 0);
	writeRegister(I2CExpRegisters::MCP23008_GPPU, 0);
	writeRegister(I2CExpRegisters::MCP23008_INTF, 0);
	writeRegister(I2CExpRegisters::MCP23008_INTCAP, 0);
	writeRegister(I2CExpRegisters::MCP23008_GPIO, 0);
	writeRegister(I2CExpRegisters::MCP23008_OLAT, 0);
}

CI2CPortExpander::CI2CPortExpander(byte i2cAddress)
{
	m_address = i2cAddress;

	CI2CPortExpander();
}

CI2CPortExpander::~CI2CPortExpander()
{
}

void CI2CPortExpander::setPortBit(I2CExpPorts targetPort, I2CExpRegisterBit regBit, byte* m_pRegByte)
{
	I2CExpPortBits portBit;

	switch (targetPort)
	{
	case I2CExpPorts::PORT_GP0:
		portBit = I2CExpPortBits::PORT_GP0_BIT;
		break;
	case I2CExpPorts::PORT_GP1:
		portBit = I2CExpPortBits::PORT_GP1_BIT;
		break;
	case I2CExpPorts::PORT_GP2:
		portBit = I2CExpPortBits::PORT_GP2_BIT;
		break;
	case I2CExpPorts::PORT_GP3:
		portBit = I2CExpPortBits::PORT_GP3_BIT;
		break;
	case I2CExpPorts::PORT_GP4:
		portBit = I2CExpPortBits::PORT_GP4_BIT;
		break;
	case I2CExpPorts::PORT_GP5:
		portBit = I2CExpPortBits::PORT_GP5_BIT;
		break;
	case I2CExpPorts::PORT_GP6:
		portBit = I2CExpPortBits::PORT_GP6_BIT;
		break;
	case I2CExpPorts::PORT_GP7:
		portBit = I2CExpPortBits::PORT_GP7_BIT;
		break;
	}

	if (regBit == I2CExpRegisterBit::High)
		*m_pRegByte |= (byte)portBit; // Set the bit
	else
		*m_pRegByte &= ~(byte)portBit; // Clear the bit
}

// This function sets the IO direction for GPIO
void CI2CPortExpander::setIODIR(I2CExpPorts targetPort, I2CExpIODirection ioDir, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)ioDir, &m_iodirSetting);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_IODIR, m_iodirSetting);
}

// Configure the input polarity on GPIO registers
void CI2CPortExpander::setIPOL(I2CExpPorts targetPort, I2CExpIOPolarity iPol, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)iPol, &m_iodirSetting);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_IPOL, m_iodirSetting);
}

// Sets the IOCON register value
void CI2CPortExpander::setIOCON(I2CExpPorts targetPort, I2CExpIOCONValue ioCon, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)ioCon, &m_ioconSetting);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_IOCON, m_ioconSetting);
}

// Configures the pullup resistors for GPIO
void CI2CPortExpander::setGPPU(I2CExpPorts targetPort, I2CExpGPPUEnable gppuEnable, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)gppuEnable, &m_gppuSetting);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_GPPU, m_gppuSetting);
}

// Writes to the GPIO register
void CI2CPortExpander::writeGPIO(I2CExpPorts targetPort, I2CExpGPIOValue gpioValue, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)gpioValue, &m_gpioValue);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_GPIO, m_gpioValue);
}

// Reads the GPIO register
byte CI2CPortExpander::readGPIO()
{
	return readRegister(I2CExpRegisters::MCP23008_GPIO);
}

CI2CPortExpander::I2CExpGPIOValue CI2CPortExpander::readGPIOPort(I2CExpPorts readPort)
{
	byte gpioValue = readGPIO();

	return (I2CExpGPIOValue)bitRead(gpioValue, (byte)readPort);
}

void CI2CPortExpander::setGPINTEN(I2CExpPorts targetPort, I2CExpGPINTEnable gpintEnable, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)gpintEnable, &m_gpintenSetting);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_GPINTEN, m_gpintenSetting);
}

void CI2CPortExpander::setDEFVAL(I2CExpPorts targetPort, I2CExpDEFVALComparison defValue, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)defValue, &m_defvalSetting);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_DEFVAL, m_defvalSetting);
}

void CI2CPortExpander::setINTCON(I2CExpPorts targetPort, I2CExpINTCONControl intControl, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)intControl, &m_intconSetting);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_INTCON, m_intconSetting);
}

byte CI2CPortExpander::readINTF()
{
	return readRegister(I2CExpRegisters::MCP23008_INTF);
}

byte CI2CPortExpander::readINTCAP()
{
	return readRegister(I2CExpRegisters::MCP23008_INTCAP);
}

byte CI2CPortExpander::readOLAT()
{
	return readRegister(I2CExpRegisters::MCP23008_OLAT);
}

void CI2CPortExpander::writeOLAT(I2CExpPorts targetPort, I2CExpOLATValue olatValue, bool updateFlag)
{
	setPortBit(targetPort, (I2CExpRegisterBit)olatValue, &m_olatSetting);

	if (updateFlag)
		writeRegister(I2CExpRegisters::MCP23008_DEFVAL, m_olatSetting);
}

void CI2CPortExpander::writeRegister(I2CExpRegisters targetRegister, byte outValue)
{
	Log("Writing to register %x\n", targetRegister);

	Wire.beginTransmission(m_address);
	Wire.write((byte)targetRegister);
	Wire.write(outValue);
	Wire.endTransmission();
}

byte CI2CPortExpander::readRegister(I2CExpRegisters targetRegister)
{
	Log("Reading from register %x\n", targetRegister);

	Wire.beginTransmission(m_address);
	Wire.write((byte)targetRegister);
	Wire.endTransmission();

	Wire.requestFrom(m_address, 0x01);

	if (Wire.available())
		return (byte)Wire.read(); // Technically the read returns a ULONG but as this is an MCP23008 its actually a single byte
	else
		return 0; // TODO: Determine whether or not there needs to be a read error return for this function
}