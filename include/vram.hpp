#pragma once

#include <array>
#include <cstdint>

class Vram
{
public:
    std::array<uint8_t, 65535> data;


    Vram();

    void reset();
    uint16_t read16(uint16_t address);
    void write16(uint16_t address, uint16_t value);
    void write8(uint16_t address, uint8_t value);
};