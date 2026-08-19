#include <opcodes.hpp>
#include <cpu.hpp>

bool isHlt(bool debug, Cpu& cpu)
{
    if (debug)
        std::cout << "Instruction: hlt" << std::endl;
    return false;
}

bool isMov(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value2)
{
    if (debug)
        std::cout << "Instruction : mov ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(arg1, value2);
    if (debug)
        std::cout << cpu.getRegisterName(arg1) << " = " << cpu.getRegister(arg1) << std::endl;
    return true;
}

bool isAdd(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2)
{
    if (debug)
        std::cout << "Instruction : add ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(arg1, value1 + value2);
    if (debug)
        std::cout << cpu.getRegisterName(arg1) << " = " << cpu.getRegister(arg1) << std::endl;
    return true;
}

bool isSub(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2)
{
    if (debug)
        std::cout << "Instruction : sub ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(arg1, value1 - value2);
    if (debug)
        std::cout << cpu.getRegisterName(arg1) << " = " << cpu.getRegister(arg1) << std::endl;
    return true;
}

bool isXor(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2)
{
    if (debug)
        std::cout << "Instruction : xor ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(arg1, value1 ^ value2);
    if (debug)
        std::cout << cpu.getRegisterName(arg1) << " = " << cpu.getRegister(arg1) << std::endl;
    return true;
}

bool isOr(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2)
{
    if (debug)
        std::cout << "Instruction : or ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(arg1, value1 | value2);
    if (debug)
        std::cout << cpu.getRegisterName(arg1) << " = " << cpu.getRegister(arg1) << std::endl;
    return true;
}

bool isInc(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : inc ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(arg1, value1 + 1);
    if (debug)
        std::cout << cpu.getRegisterName(arg1) << " = " << cpu.getRegister(arg1) << std::endl;
    return true;
}

bool isDec(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : dec ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(arg1, value1 - 1);
    if (debug)
        std::cout << cpu.getRegisterName(arg1) << " = " << cpu.getRegister(arg1) << std::endl;
    return true;
}

bool isJmp(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : jmp ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(0x0A, value1);
    return true;
}

bool isJie(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : jie ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if (((cpu.FL >> 14) & 0b11) == 0b01)
        cpu.setRegister(0x0A, value1);
    else
    {
        if (debug)
            std::cout << "condition not met" << std::endl;
        cpu.IP += 4;
    }
    return true;
}

bool isJig(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : jig ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if (((cpu.FL >> 12) & 0b11) == 0b01)
        cpu.setRegister(0x0A, value1);
    else
    {
        if (debug)
            std::cout << "condition not met" << std::endl;
        cpu.IP += 4;
    }
    return true;
}

bool isJil(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : jil ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if (((cpu.FL >> 10) & 0b11) == 0b01)
        cpu.setRegister(0x0A, value1);
    else
    {
        if (debug)
            std::cout << "condition not met" << std::endl;
        cpu.IP += 4;
    }
    return true;
}

bool isJeg(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : jeg ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if ((((cpu.FL >> 14) & 0b11) == 0b01) || (((cpu.FL >> 12) & 0b11) == 0b01))
        cpu.setRegister(0x0A, value1);
    else
    {
        if (debug)
            std::cout << "condition not met" << std::endl;
        cpu.IP += 4;
    }
    return true;
}

bool isJel(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : jel ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if ((((cpu.FL >> 14) & 0b11) == 0b01) || (((cpu.FL >> 10) & 0b11) == 0b01))
        cpu.setRegister(0x0A, value1);
    else
    {
        if (debug)
            std::cout << "condition not met" << std::endl;
        cpu.IP += 4;
    }
    return true;
}

bool isJne(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : jne ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if (((cpu.FL >> 14) & 0b11) == 0b00)
        cpu.setRegister(0x0A, value1);
    else
    {
        if (debug)
            std::cout << "condition not met" << std::endl;
        cpu.IP += 4;
    }
    return true;
}

bool isCmp(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2)
{
    if (debug)
        std::cout << "Instruction : cmp ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << ", ";
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.FL = 0x0000; 

    if (value1 == value2)
        cpu.FL |= (0b01 << 14);
    else if (value1 > value2)
        cpu.FL |= (0b01 << 12);
    else if (value1 < value2)
        cpu.FL |= (0b01 << 10);
    if (debug)
        std::cout << cpu.getRegisterName(0x0B) << " = " << cpu.getRegister(0x0B) << std::endl;
    return true;
}

bool isCall(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : call ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.pushed[cpu.SP] = cpu.IP + 4;
    cpu.SP ++;
    cpu.setRegister(0x0A, value1);
    return true;
}

bool isRet(bool debug, Cpu& cpu)
{
    if (debug)
        std::cout << "Instruction : ret" << std::endl;
    cpu.SP --;
    cpu.IP = cpu.pushed[cpu.SP];
    return true;
}

bool isPush(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : push ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if (debug)
        std::cout << "Valeur poussee : " << value1 << std::endl;
    cpu.pushed[cpu.SP] = value1;
    cpu.SP ++;
    return true;
}

bool isPop(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    if (debug)
        std::cout << "Instruction : pop ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.SP --;
    cpu.setRegister(arg1, cpu.pushed[cpu.SP]);
    value1 = cpu.getRegister(arg1);
    if (debug)
        std::cout << "Valeur tiree : " << value1 << std::endl;
    return true;
}

bool isLdRam(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2)
{
    bool inReg = false;
    bool inAdr = false;
    bool inPtr = false;
    if (debug)
        std::cout << "Instruction : ldram ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        inReg = true;
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;

    case 0x02:
        if (debug)
            std::cout << "0x" << std::hex << arg1 << std::dec << ", ";
        inAdr = true;
        break;

    case 0x03:
        if (debug)
            std::cout << "0x" << std::hex << cpu.getRegister(arg1) << std::dec << ", ";
        inPtr = true;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;

    case 0x02:
        if (debug)
            std::cout << "0x" << std::hex << arg2 << std::dec << std::endl;
        value2 = cpu.bus->read16(arg2 + 0x10000);
        break;

    case 0x03:
        if (debug)
            std::cout << "0x" << std::hex << cpu.getRegister(arg2) << std::dec << std::endl;
        value2 = cpu.bus->read16(cpu.getRegister(arg2) + 0x10000);
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if (inReg)
    {
        if (debug)
            std::cout << "Utilisez mov pour ceci" << std::endl;
    }
    else if (inAdr)
    {
        cpu.bus->write8(static_cast<uint32_t>(arg1) + 0x10000, value2);
        if (debug)
            std::cout << "0x" << std::hex << arg1 << std::dec << " = " << value2 << std::endl;
    }
    else if (inPtr)
    {
        cpu.bus->write8(static_cast<uint32_t>(cpu.getRegister(arg1)) + 0x10000, value2);
        if (debug)
            std::cout << "0x" << std::hex << cpu.getRegister(arg1) << std::dec << " = " << value2 << std::endl;
    }
    return true;
}

bool isLdVrm(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2)
{
    bool inReg = false;
    bool inAdr = false;
    bool inPtr = false;
    if (debug)
        std::cout << "Instruction : ldvrm ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        inReg = true;
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;

    case 0x02:
        if (debug)
            std::cout << "0x" << std::hex << arg1 << std::dec << ", ";
        inAdr = true;
        break;

    case 0x03:
        if (debug)
            std::cout << "0x" << std::hex << cpu.getRegister(arg1) << std::dec << ", ";
        inPtr = true;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;

    case 0x02:
        if (debug)
            std::cout << "0x" << std::hex << arg2 << std::dec << std::endl;
        value2 = cpu.bus->read16(arg2 + 0x20000);
        break;

    case 0x03:
        if (debug)
            std::cout << "0x" << std::hex << cpu.getRegister(arg2) << std::dec << std::endl;
        value2 = cpu.bus->read16(cpu.getRegister(arg2) + 0x20000);
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    if (inReg)
    {
        if (debug)
            std::cout << "Utilisez mov pour ceci" << std::endl;
    }
    else if (inAdr)
    {
        cpu.bus->write8(static_cast<uint32_t>(arg1) + 0x20000, value2);
        if (debug)
            std::cout << "0x" << std::hex << arg1 << std::dec << " = " << value2 << std::endl;
    }
    else if (inPtr)
    {
        cpu.bus->write8(static_cast<uint32_t>(cpu.getRegister(arg1)) + 0x20000, value2);
        if (debug)
            std::cout << "0x" << std::hex << cpu.getRegister(arg1) << std::dec << " = " << value2 << std::endl;
    }
    return true;
}

bool isInt(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1)
{
    static std::string nextTrack = "";
    if (debug)
        std::cout << "Instruction : Int ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << std::endl;
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg1 << std::endl;
        value1 = (int)arg1;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (value1)
    {
    case 0x0000:
        cpu.bus->ram->reset();
        cpu.bus->rom->reset();
        cpu.bus->vram->reset();
        cpu.gpu->reset();
        cpu.reset();
        break;
    case 0x0001:
        cpu.gpu->vram.data = cpu.bus->vram->data;
        cpu.gpuUpdate = true;
        break;
    case 0x0002:
        cpu.bus->vram->data = cpu.bus->ram->data;
        break;
    case 0x0003:
        cpu.gpu->getKey();
        cpu.A = cpu.gpu->convertKey(cpu.gpu->key);
        cpu.gpu->keyPressed = false;
        break;
    case 0x0004:
        cpu.A = cpu.gpu->keyPressed;
        cpu.B = cpu.gpu->convertKey(cpu.gpu->key);
        cpu.gpu->keyPressed = false;
        break;
    case 0x0005:
        cpu.C = cpu.hd->read8(cpu.A, cpu.B);
        break;
    case 0x0006:
        cpu.hd->write8(cpu.A, cpu.B, cpu.C);
        break;
    case 0x0007:
        nextTrack = getFilePath(cpu.A); 
        if (debug)
            std::cout << "Selected file: " << nextTrack << std::endl;
        break;
    case 0x0008:
        if (!nextTrack.empty())
        {
            if (debug)
                std::cout << "Loading" << nextTrack << " onto sector " << cpu.A << "..." << std::endl;
            cpu.hd->writeFileToSector(nextTrack, cpu.A);
        }
        else if (debug)
        {
            std::cerr << "Error: Invalid or unspecified file path!" << std::endl;
        }
        break;
    case 0x0009:
        cpu.hd->loadInRom(cpu.A, *cpu.bus->rom);
        cpu.IP = -4;
        cpu.running = true;
        break;
    case 0x000a:
        cpu.gpu->drawChar(cpu.A, cpu);
        break;
    case 0x000b:
        cpu.gpu->cursorPos = (cpu.C % 32) * 8 + (cpu.C / 32) * 2048;
        break;
    case 0x000c:
        cpu.bus->vram->reset();
        break;
    default:
        break;
    }
    return true;
}

bool isMul(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2)
{
    if (debug)
        std::cout << "Instruction : mul ";
    switch (type1)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg1) << ", ";
        value1 = cpu.getRegister(arg1);
        break;

    case 0x01:
        if (debug)
            std::cout << "Impossible to store in a number" << std::endl;
        return false;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    switch (type2)
    {
    case 0x00:
        if (debug)
            std::cout << cpu.getRegisterName(arg2) << std::endl;
        value2 = cpu.getRegister(arg2);
        break;

    case 0x01:
        if (debug)
            std::cout << (int)arg2 << std::endl;
        value2 = (int)arg2;
        break;
    
    default:
        if (debug)
            std::cout << "Invalid type" << std::endl;
        return false;
    }

    cpu.setRegister(arg1, value1 * value2);
    if (debug)
        std::cout << cpu.getRegisterName(arg1) << " = " << cpu.getRegister(arg1) << std::endl;
    return true;
}

