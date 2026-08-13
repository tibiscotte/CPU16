#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

class Cpu;

bool isHlt(bool debug, Cpu& cpu);
bool isMov(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value2);
bool isAdd(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2);
bool isSub(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2);
bool isXor(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2);
bool isOr(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2);
bool isInc(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isDec(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isJmp(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isJie(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isJig(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isJil(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isJeg(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isJel(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isJne(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isCmp(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2);
bool isCall(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isRet(bool debug, Cpu& cpu);
bool isPush(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isPop(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isLdRam(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2);
bool isLdVrm(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2);
bool isInt(bool debug, uint8_t type1, Cpu& cpu, uint16_t arg1, uint16_t value1);
bool isMul(bool debug, uint8_t type1, uint8_t type2, Cpu& cpu, uint16_t arg1, uint16_t arg2, uint16_t value1, uint16_t value2);