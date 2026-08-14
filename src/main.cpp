#include <cpu.hpp>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }
    
    Cpu cpu;
    Gpu gpu;
    Bus bus;
    Rom rom;
    Ram ram;
    Vram vram;

    HardDisk* hd = new HardDisk();

    if (!gpu.init())
    {
        delete hd;
        return 1;
    }

    hd->writeFileToSector(argv[1], 0x0000);

    hd->loadInRom(0x0000, rom);

    bus.rom = &rom;
    bus.ram = &ram;
    bus.vram = &vram;

    cpu.bus = &bus;
    cpu.gpu = &gpu;
    cpu.hd = hd;

    std::string debug = argv[2];

    if (debug == "true")
        cpu.debug = true;
    else if (debug == "false")
        cpu.debug = false;
    else
    {
        std::cout << "Second invalid argument" << std::endl;
        return 1;
    }

    while (cpu.running && gpu.running)
    {
        gpu.handleEvents();

        cpu.step();

        if (cpu.gpuUpdate)
        {
            gpu.drawScreen();
            cpu.gpuUpdate = false;
        }
    }

    delete hd;

    return 0;
}