#include <bus.hpp>

uint16_t Bus::read16(uint32_t address)
{
    if (address >= 0x00000 && address < 0x10000)
    {
        return rom->read16(address);
    }

    else if (address >= 0x10000 && address < 0x20000)
    {
        return ram->read16(address - 0x10000);
    }

    else if (address >= 0x20000 && address < 0x30000)
    {
        return vram->read16(address - 0x20000);
    }
    return 0x0000;
}

void Bus::write16(uint32_t address, uint16_t value)
{
    if (address >= 0x00000 && address < 0x10000)
    {
        return;
    }

    else if (address >= 0x10000 && address < 0x20000)
    {
        ram->write16(address - 0x10000, value);
    }

    else if (address >= 0x20000 && address < 0x30000)
    {
        vram->write16(address - 0x20000, value);
    }
}

void Bus::write8(uint32_t address, uint8_t value)
{
    if (address >= 0x00000 && address < 0x10000)
        return;

    else if (address >= 0x10000 && address < 0x20000)
        ram->write8(address - 0x10000, value);

    else if (address >= 0x20000 && address < 0x30000)
        vram->write8(address - 0x20000, value);
}