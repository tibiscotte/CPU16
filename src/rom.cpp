#include <rom.hpp>

Rom::Rom()
{
    reset();
}

void Rom::reset()
{
    data.fill(0x00);
}

uint16_t Rom::read16(uint16_t address)
{
    return (data[address] << 8) | data[address + 1];
}

void Rom::loadFromDisk(uint16_t address, uint8_t value)
{
    data[address] = value;
}