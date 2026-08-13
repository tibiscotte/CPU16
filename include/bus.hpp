#pragma once

#include <cstdint>
#include <rom.hpp>
#include <ram.hpp>
#include <vram.hpp>

class Bus
{
public:
    Rom *rom;
    Ram *ram;
    Vram *vram;


    uint16_t read16(uint32_t address);
    void write16(uint32_t address, uint16_t value);
    void write8(uint32_t address, uint8_t value);
};