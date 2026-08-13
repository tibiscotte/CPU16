#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>

class Rom
{
public:
    std::array<uint8_t, 65535> data;


    Rom();

    void reset();
    uint16_t read16(uint16_t address);
    void loadFromDisk(uint16_t address, uint8_t value);
};