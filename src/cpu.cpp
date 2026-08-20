#include <cpu.hpp>
#include <unordered_map>
#include <string>

std::unordered_map<uint16_t, std::string> fileTable = {
    { 0x0000, "../roms/boot.the" }
};

std::string getFilePath(uint16_t fileId)
{
    if (fileTable.find(fileId) != fileTable.end()) {
        return fileTable[fileId];
    }
    return "";
}

Cpu::Cpu()
{
    for (uint32_t i = 1; i < 0x10000; i++)
    {
        fileTable[i] = "../roms/track" + std::to_string(i) + ".the";
    }
    
    bus = nullptr;
    gpu = nullptr;
    hd = nullptr;

    reset();
    IP = 0;
}

void Cpu::reset()
{
    A = B = C = D = 0;
    W = X = Y = Z = 0;
    SP = BP = FL = 0;

    pushed.fill(0x0000);

    running = true;

    gpuUpdate = false;
}

void Cpu::step()
{
    uint16_t instruction = bus->read16(IP);

    uint8_t opcode = instruction >> 8;
    uint8_t info = instruction & 0xFF;

    uint8_t type1 = (info >> 4) & 0x0F;
    uint8_t type2 = info & 0x0F;

    uint16_t arg1 = bus->read16(IP + 2);
    uint16_t arg2 = bus->read16(IP + 4);

    uint16_t value1 = 0;
    uint16_t value2 = 0;

    switch(opcode)
    {
    case 0x00:
        running = isHlt(debug, *this);
        break;
    
    case 0x01:
        running = isMov(debug, type1, type2, *this, arg1, arg2, value2);
        IP += 6;
        break;

    case 0x02:
        running = isAdd(debug, type1, type2, *this, arg1, arg2, value1, value2);
        IP += 6;
        break;

    case 0x03:
        running = isSub(debug, type1, type2, *this, arg1, arg2, value1, value2);
        IP += 6;
        break;

    case 0x04:
        running = isXor(debug, type1, type2, *this, arg1, arg2, value1, value2);
        IP += 6;
        break;

    case 0x05:
        running = isOr(debug, type1, type2, *this, arg1, arg2, value1, value2);
        IP += 6;
        break;

    case 0x06:
        running = isInc(debug, type1, *this, arg1, value1);
        IP += 4;
        break;
    
    case 0x07:
        running = isDec(debug, type1, *this, arg1, value1);
        IP += 4;
        break;

    case 0x08:
        running = isJmp(debug, type1, *this, arg1, value1);
        break;

    case 0x09:
        running = isJie(debug, type1, *this, arg1, value1);
        break;

    case 0x0a:
        running = isJig(debug, type1, *this, arg1, value1);
        break;

    case 0x0b:
        running = isJil(debug, type1, *this, arg1, value1);
        break;

    case 0x0c:
        running = isJeg(debug, type1, *this, arg1, value1);
        break;

    case 0x0d:
        running = isJel(debug, type1, *this, arg1, value1);
        break;

    case 0x0e:
        running = isJne(debug, type1, *this, arg1, value1);
        break;

    case 0x0f:
        running = isCmp(debug, type1, type2, *this, arg1, arg2, value1, value2);
        IP += 6;
        break;

    case 0x10:
        running = isCall(debug, type1, *this, arg1, value1);
        break;

    case 0x11:
        running = isRet(debug, *this);
        break;

    case 0x12:
        running = isPush(debug, type1, *this, arg1, value1);
        IP += 4;
        break;

    case 0x13:
        running = isPop(debug, type1, *this, arg1, value1);
        IP += 4;
        break;

    case 0x14:
        running = isLdRam(debug, type1, type2, *this, arg1, arg2, value1, value2);
        IP += 6;
        break;

    case 0x15:
        running = isLdVrm(debug, type1, type2, *this, arg1, arg2, value1, value2);
        IP += 6;
        break;

    case 0x16:
        running = isInt(debug, type1, *this, arg1, value1);
        IP += 4;
        break;

    case 0x17:
        running = isMul(debug, type1, type2, *this, arg1, arg2, value1, value2);
        IP += 6;
        break;

    default:
        if (debug)
            std::cout << "Invalid opcode" << std::endl;
        running = false;
    }
}

uint16_t Cpu::getRegister(uint16_t reg)
{
    switch (reg)
    {
    case 0x00: return A;
    case 0x01: return B;
    case 0x02: return C;
    case 0x03: return D;
    case 0x04: return W;
    case 0x05: return X;
    case 0x06: return Y;
    case 0x07: return Z;
    case 0x08: return SP;
    case 0x09: return BP;
    case 0x0A: return IP;
    case 0x0B: return FL;
    
    default:
        return 0;
    }
}

const char* Cpu::getRegisterName(uint16_t reg)
{
    switch (reg)
    {
    case 0x00: return "A";
    case 0x01: return "B";
    case 0x02: return "C";
    case 0x03: return "D";
    case 0x04: return "W";
    case 0x05: return "X";
    case 0x06: return "Y";
    case 0x07: return "Z";
    case 0x08: return "SP";
    case 0x09: return "BP";
    case 0x0A: return "IP";
    case 0x0B: return "FL";
    default:   return "??";
    }
}

void Cpu::setRegister(uint16_t reg, uint16_t value)
{
    switch (reg)
    {
    case 0x00: A = value; break;
    case 0x01: B = value; break;
    case 0x02: C = value; break;
    case 0x03: D = value; break;
    case 0x04: W = value; break;
    case 0x05: X = value; break;
    case 0x06: Y = value; break;
    case 0x07: Z = value; break;
    case 0x08: SP = value; break;
    case 0x09: BP = value; break;
    case 0x0A: IP = value; break;
    case 0x0B: FL = value; break;
    }
}