#include <vram.hpp>

Vram::Vram()
{
    reset();
}

void Vram::reset()
{
    data.fill(0x00);
}

uint16_t Vram::read16(uint16_t address)
{
    return (data[address] << 8) | data[address + 1];
}

void Vram::write16(uint16_t address, uint16_t value)
{
    data[address] = (value >> 8) & 0xFF;
    data[address + 1] = value & 0xFF;
}

void Vram::write8(uint16_t address, uint8_t value)
{
    data[address] = value;
}