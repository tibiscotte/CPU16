#pragma once

#include <cstdint>
#include <bus.hpp>
#include <gpu.hpp>
#include <opcodes.hpp>
#include <hardDisk.hpp>

std::string getFilePath(uint16_t fileId);

class Cpu
{
public:
    uint16_t A, B, C, D, W, X, Y, Z;
    uint16_t SP, BP, IP, FL;

    bool running;
    bool debug;

    bool gpuUpdate;

    std::array<uint16_t, 32> pushed;

    Bus *bus;
    Gpu *gpu;
    HardDisk *hd;


    Cpu();

    void reset();
    void step();
    uint16_t getRegister(uint16_t reg);
    const char* getRegisterName(uint16_t reg);
    void setRegister(uint16_t reg, uint16_t value);
};