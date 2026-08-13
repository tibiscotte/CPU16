#include <ram.hpp>

Ram::Ram()
{
    reset();
}

void Ram::reset()
{
    data.fill(0x00);
}

uint16_t Ram::read16(uint16_t address)
{
    return (data[address] << 8) | data[address + 1];
}

void Ram::write16(uint16_t address, uint16_t value)
{
    data[address] = (value >> 8) & 0xFF;
    data[address + 1] = value & 0xFF;
}

void Ram::write8(uint16_t address, uint8_t value)
{
    data[address] = value;
}