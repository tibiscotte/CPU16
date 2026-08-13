#include <cpu.hpp>

int main()
{
    Cpu cpu;
    Gpu gpu;
    Bus bus;
    Rom rom;
    Ram ram;
    Vram vram;

    HardDisk* hd = new HardDisk();

    std::system("TheAsm ../roms/theo.theasm ../roms/theo.the");

    if (!gpu.init())
    {
        delete hd;
        return 1;
    }

    hd->writeFileToSector("../roms/theo.the", 0x0000);

    std::cout << "Premier octet : "
              << static_cast<int>(hd->read8(0x0000, 0x0000))
              << '\n';

    hd->loadInRom(0x0000, rom);

    bus.rom = &rom;
    bus.ram = &ram;
    bus.vram = &vram;

    cpu.bus = &bus;
    cpu.gpu = &gpu;
    cpu.hd = hd;

    cpu.debug = false;

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