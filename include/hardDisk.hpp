#pragma once

#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include <nlohmann/json.hpp>

#include <rom.hpp>

class HardDisk
{
public:
    static constexpr uint32_t SECTION_COUNT = 65536;
    static constexpr uint32_t SECTION_SIZE = 512;

    std::vector<std::array<uint8_t, SECTION_SIZE>> data;

    HardDisk();
    ~HardDisk();

    void load();
    void save();

    void write8(uint16_t section, uint16_t offset, uint8_t value);
    uint8_t read8(uint16_t section, uint16_t offset);

    void loadInRom(uint16_t section, Rom& rom);

    void writeFileToSector(
        const std::string& filename,
        uint16_t section
    );
};