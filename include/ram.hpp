#pragma once

#include <array>
#include <cstdint>

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

class Ram
{
public:
    std::array<uint8_t, 65535> data;

    Ram();
    ~Ram();

    void reset();
    uint16_t read16(uint16_t address);
    uint8_t read8(uint16_t address);
    void write16(uint16_t address, uint16_t value);
    void write8(uint16_t address, uint8_t value);
    void save();
};