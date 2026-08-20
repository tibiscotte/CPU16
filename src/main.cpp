#include <cpu.hpp>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: cpu16 <t|f> [rom-file]" << std::endl;
        return 1;
    }

    if (argc >= 3)
        std::cout << "ROM file: " << argv[2] << std::endl;
    
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

    if (argc >= 3)
        hd->writeFileToSector(argv[2], 0x0000);

    hd->loadInRom(0x0000, rom);

    bus.rom = &rom;
    bus.ram = &ram;
    bus.vram = &vram;

    cpu.bus = &bus;
    cpu.gpu = &gpu;
    cpu.hd = hd;

    gpu.drawScreen();

    std::string debug = argv[1];

    if (debug == "t")
        cpu.debug = true;
    else if (debug == "f")
        cpu.debug = false;
    else
    {
        std::cout << "Second invalid argument" << std::endl;
        return 1;
    }

    while (gpu.running)
    {
        gpu.handleEvents();

        if (cpu.running)
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