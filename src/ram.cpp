#include <ram.hpp>

using json = nlohmann::json;

Ram::Ram()
{
    reset();
}

Ram::~Ram()
{
    save();
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

void Ram::save()
{
    json j;

    j["data"] = data;

    std::ofstream file("../src/json/ram_backup.json");

    if (!file)
    {
        std::cerr << "Erreur : impossible d'ouvrir ram_backup.json" << std::endl;
        return;
    }

    file << j.dump(4);
}