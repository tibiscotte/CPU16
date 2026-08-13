#include <hardDisk.hpp>

using json = nlohmann::json;

HardDisk::HardDisk()
{
    data.resize(SECTION_COUNT);

    for (auto& section : data)
        section.fill(0);

    load();
}

HardDisk::~HardDisk()
{
    save();
}

void HardDisk::load()
{
    std::ifstream file("../src/json/hard_disk.json");

    if (!file.is_open())
        return;

    try {
        json j;
        file >> j;

        for (auto& [sectionName, sectionData] : j["harddisk"]["sections"].items())
        {
            uint16_t section = std::stoul(sectionName, nullptr, 16);

            for (uint16_t i = 0; i < sectionData.size(); i++)
            {
                data[section][i] = sectionData[i];
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur de lecture du JSON HardDisk : " << e.what() << std::endl;
    }
}

void HardDisk::save()
{
    json j;

    j["harddisk"]["section_size"] = 512;
    j["harddisk"]["section_count"] = 65536;
    j["harddisk"]["sections"] = json::object();

    for (uint32_t section = 0; section < 65536; section++)
    {
        bool used = false;

        for (uint32_t i = 0; i < 512; i++)
        {
            if (data[section][i] != 0)
            {
                used = true;
                break;
            }
        }

        if (!used)
            continue;

        std::stringstream ss;

        ss << "0x"
           << std::uppercase
           << std::hex
           << std::setw(4)
           << std::setfill('0')
           << section;

        j["harddisk"]["sections"][ss.str()] = data[section];
    }

    std::ofstream file("../src/json/hard_disk.json");

    file << j.dump(4);
}

void HardDisk::write8(uint16_t section, uint16_t offset, uint8_t value)
{
    data[section][offset] = value;
}

uint8_t HardDisk::read8(uint16_t section, uint16_t offset)
{
    return data[section][offset];
}

void HardDisk::loadInRom(uint16_t section, Rom& rom)
{
    uint16_t address = 0;

    while (address < rom.data.size())
    {
        for (uint16_t i = 0; i < 512 && address < rom.data.size(); i++)
        {
            rom.loadFromDisk(address, data[section][i]);
            address++;
        }

        section++;
    }
}

void HardDisk::writeFileToSector(const std::string& filename, uint16_t section)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open())
        return;

    uint16_t currentSection = section;
    uint16_t offset = 0;

    char byte;

    while (file.get(byte))
    {
        data[currentSection][offset] = static_cast<uint8_t>(byte);

        offset++;

        if (offset == 512)
        {
            offset = 0;
            currentSection++;
        }
    }

    file.close();
}