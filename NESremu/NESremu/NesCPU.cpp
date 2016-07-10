#include "NesCpu.h"

namespace NesCPU
{
    //Tables
    void (*AddrModesTable[256])() = {
        /* 0xVH  0    1     2    3    4    5    6    7    8    9     A    B    C     D     E     F  */
        /* 0 */  imp, indx, imp, imp, imp, zp,  zp,  imp, imp, imm,  acc, imp, imp,  abs,  abs,  imp,
        /* 1 */  rel, indy, imp, imp, imp, zpx, zpx, imp, imp, absy, imp, imp, imp,  absx, absx, imp,
        /* 2 */  abs, indx, imp, imp, zp,  zp,  zp,  imp, imp, imm,  acc, imp, abs,  abs,  abs,  imp,
        /* 3 */  rel, indy, imp, imp, imp, zpx, zpx, imp, imp, absy, imp, imp, imp,  absx, absx, imp,
        /* 4 */  imp, indx, imp, imp, imp, zp,  zp,  imp, imp, imm,  acc, imp, abs,  abs,  abs,  imp,
        /* 5 */  rel, indy, imp, imp, imp, zpx, zpx, imp, imp, absy, imp, imp, imp,  absx, absx, imp,
        /* 6 */  imp, indx, imp, imp, imp, zp,  zp,  imp, imp, imm,  acc, imp, ind,  abs,  abs,  imp,
        /* 7 */  rel, indy, imp, imp, imp, zpx, zpx, imp, imp, absy, imp, imp, imp,  absx, absx, imp,
        /* 8 */  imp, indx, imp, imp, zp,  zp,  zp,  imp, imp, imp,  imp, imp, abs,  abs,  abs,  imp,
        /* 9 */  rel, indy, imp, imp, zpx, zpx, zpy, imp, imp, absy, imp, imp, imp,  absx, imp,  imp,
        /* A */  imm, indx, imm, imp, zp,  zp,  zp,  imp, imp, imm,  imp, imp, abs,  abs,  abs,  imp,
        /* B */  rel, indy, imp, imp, zpx, zpx, zpy, imp, imp, absy, imp, imp, absx, absx, absy, imp,
        /* C */  imm, indx, imp, imp, zp,  zp,  zp,  imp, imp, imm,  imp, imp, abs,  abs,  abs,  imp,
        /* D */  rel, indy, imp, imp, imp, zpx, zpx, imp, imp, absy, imp, imp, imp,  absx, absx, imp,
        /* E */  imm, indx, imp, imp, zp,  zp,  zp,  imp, imp, imm,  imp, imp, abs,  abs,  abs,  imp,
        /* F */  rel, indy, imp, imp, imp, zpx, zpx, imp, imp, absy, imp, imp, imp,  absx, absx, imp };

    ///* 0xVH  0    1     2    3    4    5    6    7    8    9     A    B    C     D     E     F  */
    ///* 0 */  imp, indx, ---, ---, ---, zp,  zp,  ---, imp, imm,  acc, ---, ---,  abs,  abs,  ---,
    ///* 1 */  rel, indy, ---, ---, ---, zpx, zpx, ---, imp, absy, ---, ---, ---,  absx, absx, ---,
    ///* 2 */  abs, indx, ---, ---, zp,  zp,  zp,  ---, imp, imm,  acc, ---, abs,  abs,  abs,  ---,
    ///* 3 */  rel, indy, ---, ---, ---, zpx, zpx, ---, imp, absy, ---, ---, ---,  absx, absx, ---,
    ///* 4 */  imp, indx, ---, ---, ---, zp,  zp,  ---, imp, imm,  acc, ---, abs,  abs,  abs,  ---,
    ///* 5 */  rel, indy, ---, ---, ---, zpx, zpx, ---, imp, absy, ---, ---, ---,  absx, absx, ---,
    ///* 6 */  imp, indx, ---, ---, ---, zp,  zp,  ---, imp, imm,  acc, ---, ind,  abs,  abs,  ---,
    ///* 7 */  rel, indy, ---, ---, ---, zpx, zpx, ---, imp, absy, ---, ---, ---,  absx, absx, ---,
    ///* 8 */  ---, indx, ---, ---, zp,  zp,  zp,  ---, imp, ---,  imp, ---, abs,  abs,  abs,  ---,
    ///* 9 */  rel, indy, ---, ---, zpx, zpx, zpy, ---, imp, absy, imp, ---, ---,  absx, ---,  ---,
    ///* A */  imm, indx, imm, ---, zp,  zp,  zp,  ---, imp, imm,  imp, ---, abs,  abs,  abs,  ---,
    ///* B */  rel, indy, ---, ---, zpx, zpx, zpy, ---, imp, absy, imp, ---, absx, absx, absy, ---,
    ///* C */  imm, indx, ---, ---, zp,  zp,  zp,  ---, imp, imm,  imp, ---, abs,  abs,  abs,  ---,
    ///* D */  rel, indy, ---, ---, ---, zpx, zpx, ---, imp, absy, ---, ---, ---,  absx, absx, ---,
    ///* E */  imm, indx, ---, ---, zp,  zp,  zp,  ---, imp, imm,  imp, ---, abs,  abs,  abs,  ---,
    ///* F */  rel, indy, ---, ---, ---, zpx, zpx, ---, imp, absy, ---, ---, ---,  absx, absx, --- 


    void (*OpcodesTable[256])() = {
        /* 0xVH  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F  */
        /* 0 */  BRK, ORA, NOP, NOP, NOP, ORA, ASL, NOP, PHP, ORA, ASL, NOP, NOP, ORA, ASL, NOP,
        /* 1 */  BPL, ORA, NOP, NOP, NOP, ORA, ASL, NOP, CLC, ORA, NOP, NOP, NOP, ORA, ASL, NOP,
        /* 2 */  JSR, AND, NOP, NOP, BIT, AND, ROL, NOP, PLP, AND, ROL, NOP, BIT, AND, ROL, NOP,
        /* 3 */  BMI, AND, NOP, NOP, NOP, AND, ROL, NOP, SEC, AND, NOP, NOP, NOP, AND, ROL, NOP,
        /* 4 */  RTI, EOR, NOP, NOP, NOP, EOR, LSR, NOP, PHA, EOR, LSR, NOP, JMP, EOR, LSR, NOP,
        /* 5 */  BVC, EOR, NOP, NOP, NOP, EOR, LSR, NOP, CLI, EOR, NOP, NOP, NOP, EOR, LSR, NOP,
        /* 6 */  RTS, ADC, NOP, NOP, NOP, ADC, ROR, NOP, PLA, ADC, ROR, NOP, JMP, ADC, ROR, NOP,
        /* 7 */  BVS, ADC, NOP, NOP, NOP, ADC, ROR, NOP, SEI, ADC, NOP, NOP, NOP, ADC, ROR, NOP,
        /* 8 */  NOP, STA, NOP, NOP, STY, STA, STX, NOP, DEY, NOP, TXA, NOP, STY, STA, STX, NOP,
        /* 9 */  BCC, STA, NOP, NOP, STY, STA, STX, NOP, TYA, STA, TXS, NOP, NOP, STA, NOP, NOP,
        /* A */  LDY, LDA, LDX, NOP, LDY, LDA, LDX, NOP, TAY, LDA, TAX, NOP, LDY, LDA, LDX, NOP,
        /* B */  BCS, LDA, NOP, NOP, LDY, LDA, LDX, NOP, CLV, LDA, TSX, NOP, LDY, LDA, LDX, NOP,
        /* C */  CPY, CMP, NOP, NOP, CPY, CMP, DEC, NOP, INY, CMP, DEX, NOP, CPY, CMP, DEC, NOP,
        /* D */  BNE, CMP, NOP, NOP, NOP, CMP, DEC, NOP, CLD, CMP, NOP, NOP, NOP, CMP, DEC, NOP,
        /* E */  CPX, SBC, NOP, NOP, CPX, SBC, INC, NOP, INX, SBC, NOP, NOP, CPX, SBC, INC, NOP,
        /* F */  BEQ, SBC, NOP, NOP, NOP, SBC, INC, NOP, SED, SBC, NOP, NOP, NOP, SBC, INC, NOP };

    ///* 0xVH  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F  */
    ///* 0 */  BRK, ORA, ---, ---, ---, ORA, ASL, ---, PHP, ORA, ASL, ---, ---, ORA, ASL, ---,
    ///* 1 */  BPL, ORA, ---, ---, ---, ORA, ASL, ---, CLC, ORA, ---, ---, ---, ORA, ASL, ---,
    ///* 2 */  JSR, AND, ---, ---, BIT, AND, ROL, ---, PLP, AND, ROL, ---, BIT, AND, ROL, ---,
    ///* 3 */  BMI, AND, ---, ---, ---, AND, ROL, ---, SEC, AND, ---, ---, ---, AND, ROL, ---,
    ///* 4 */  RTI, EOR, ---, ---, ---, EOR, LSR, ---, PHA, EOR, LSR, ---, JMP, EOR, LSR, ---,
    ///* 5 */  BVC, EOR, ---, ---, ---, EOR, LSR, ---, CLI, EOR, ---, ---, ---, EOR, LSR, ---,
    ///* 6 */  RTS, ADC, ---, ---, ---, ADC, ROR, ---, PLA, ADC, ROR, ---, JMP, ADC, ROR, ---,
    ///* 7 */  BVS, ADC, ---, ---, ---, ADC, ROR, ---, SEI, ADC, ---, ---, ---, ADC, ROR, ---,
    ///* 8 */  ---, STA, ---, ---, STY, STA, STX, ---, DEY, ---, TXA, ---, STY, STA, STX, ---,
    ///* 9 */  BCC, STA, ---, ---, STY, STA, STX, ---, TYA, STA, TXS, ---, ---, STA, ---, ---,
    ///* A */  LDY, LDA, LDX, ---, LDY, LDA, LDX, ---, TAY, LDA, TAX, ---, LDY, LDA, LDX, ---,
    ///* B */  BCS, LDA, ---, ---, LDY, LDA, LDX, ---, CLV, LDA, TSX, ---, LDY, LDA, LDX, ---,
    ///* C */  CPY, CMP, ---, ---, CPY, CMP, DEC, ---, INY, CMP, DEX, ---, CPY, CMP, DEC, ---,
    ///* D */  BNE, CMP, ---, ---, ---, CMP, DEC, ---, CLD, CMP, ---, ---, ---, CMP, DEC, ---,
    ///* E */  CPX, SBC, ---, ---, CPX, SBC, INC, ---, INX, SBC, NOP, ---, CPX, SBC, INC, ---,
    ///* F */  BEQ, SBC, ---, ---, ---, SBC, INC, ---, SED, SBC, ---, ---, ---, SBC, INC, ---

    uint32_t TicksTable[256] = {
        /* 0xVH  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  */
        /* 0 */  7, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
        /* 1 */  2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* 2 */  6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
        /* 3 */  2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* 4 */  6, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
        /* 5 */  2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* 6 */  6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
        /* 7 */  2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* 8 */  2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
        /* 9 */  2, 6, 2, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5,
        /* A */  2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
        /* B */  2, 5, 2, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
        /* C */  2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
        /* D */  2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* E */  2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
        /* F */  2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7 };

    ///* 0xVH  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  */
    ///* 0 */  7, 6, -, -, -, 3, 5, -, 3, 2, 2, -, -, 4, 6, -,
    ///* 1 */  2, 5, -, -, -, 4, 6, -, 2, 4, -, -, -, 4, 7, -,
    ///* 2 */  6, 6, -, -, 3, 3, 5, -, 4, 2, 2, -, 4, 4, 6, -,
    ///* 3 */  2, 5, -, -, -, 4, 6, -, 2, 4, -, -, -, 4, 7, -,
    ///* 4 */  6, 6, -, -, -, 3, 5, -, 3, 2, 2, -, 3, 4, 6, -,
    ///* 5 */  2, 5, -, -, -, 4, 6, -, 2, 4, -, -, -, 4, 7, -,
    ///* 6 */  6, 6, -, -, -, 3, 5, -, 4, 2, 2, -, 5, 4, 6, -,
    ///* 7 */  2, 5, -, -, -, 4, 6, -, 2, 4, -, -, -, 4, 7, -,
    ///* 8 */  -, 6, -, -, 3, 3, 3, -, 2, -, 2, -, 4, 4, 4, -,
    ///* 9 */  2, 6, -, -, 4, 4, 4, -, 2, 5, 2, -, -, 5, -, -,
    ///* A */  2, 6, 2, -, 3, 3, 3, -, 2, 2, 2, -, 4, 4, 4, -,
    ///* B */  2, 5, -, -, 4, 4, 4, -, 2, 4, 2, -, 4, 4, 4, -,
    ///* C */  2, 6, -, -, 3, 3, 5, -, 2, 2, 2, -, 4, 4, 6, -,
    ///* D */  2, 5, -, -, -, 4, 6, -, 2, 4, -, -, -, 4, 7, -,
    ///* E */  2, 6, -, -, 3, 3, 5, -, 2, 2, 2, -, 4, 4, 6, -,
    ///* F */  2, 5, -, -, -, 4, 6, -, 2, 4, -, -, -, 4, 7, -


    //Core CPU functions
    void run()
    {
        uint8_t opcode = Memory[PC];
        AddrModesTable[opcode]();
        OpcodesTable[opcode]();
        g_ticks += TicksTable[opcode] + g_tickOffset;
        //...

        //Debugging
        if (g_cpuLogEnabled) {
            printCpuLog();
        }
    }


    //Flags related functions
    void checkNegative(uint16_t val)
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_ZERO, val & 0x80);
    }

    void checkZero(uint16_t val)
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_ZERO, val == 0);
    }


    //Stack operations
    uint8_t  pull8()
    {
        return Stack[++SP];
    }

    uint16_t pull16()
    {
        return *((uint16_t*)Stack + (SP += 2));
    }

    void push8(uint8_t value)
    {
        Stack[SP--] = value;
    }

    void push16(uint16_t value)
    {
        //Check if good byte order
        *((uint16_t*)Stack + SP) = value;
        SP -= 2;
    }



    //Addressing modes

    //TO DO: Add tick offset.

    void abs()
    {
        g_srcPtr = Memory + *((uint16_t*)(Memory + PC));
        PC += 2;
    }

    void absx()
    {
        g_srcPtr = Memory + *((uint16_t*)(Memory + PC)) + X;
        PC += 2;
    }

    void absy()
    {
        g_srcPtr = Memory + *((uint16_t*)(Memory + PC)) + Y;
        PC += 2;
    }

    void acc()
    {
        g_srcPtr = &A;
    }

    void imm()
    {
        g_srcPtr = Memory + PC++;
    }

    void imp() { }

    void ind()
    {
        g_srcPtr = Memory + PC;
        PC += 2;
    }

    void indx()
    {
        uint16_t tmpAddr = Memory[(Memory[PC] + X) & 0x00FF] | (Memory[(Memory[PC++] + X + 1) & 0x00FF] << 8);
        g_srcPtr = Memory + tmpAddr;
    }

    void indy()
    {
        uint16_t tmpAddr = Memory[Memory[PC]] | (Memory[(Memory[PC++] + 1) & 0x00FF] << 8);
        g_srcPtr = Memory + tmpAddr + Y;
    }

    void rel()
    {
        g_srcPtr = Memory + PC++;
    }

    void zp()
    {
        g_srcPtr = Memory + Memory[PC++];
    }

    void zpx()
    {
        g_srcPtr = Memory + ((Memory[PC++] + X) & 0x00FF);
    }

    void zpy()
    {
        g_srcPtr = Memory + ((Memory[PC++] + Y) & 0x00FF);
    }



    //Opcodes

    //--Storage--
    void LDA()
    {
        A = *g_srcPtr;
        checkNegative(A);
        checkZero(A);
    }

    void LDX()
    {
        X = *g_srcPtr;
        checkNegative(X);
        checkZero(X);
    }

    void LDY()
    {
        Y = *g_srcPtr;
        checkNegative(Y);
        checkZero(Y);
    }

    void STA()
    {
        *g_srcPtr = A;
    }

    void STX()
    {
        *g_srcPtr = X;
    }

    void STY()
    {
        *g_srcPtr = Y;
    }

    void TAX()
    {
        X = A;
        checkNegative(X);
        checkZero(X);
    }

    void TAY()
    {
        Y = A;
        checkNegative(Y);
        checkZero(Y);
    }

    void TXA()
    {
        A = X;
        checkNegative(A);
        checkZero(A);
    }

    void TYA()
    {
        A = Y;
        checkNegative(A);
        checkZero(A);
    }

    void TSX()
    {
        X = SP;
        checkNegative(X);
        checkZero(X);
    }

    void TXS()
    {
        SP = X;
        checkNegative(SP);
        checkZero(SP);
    }


    //--Math--
    void ADC()
    {
        uint16_t temp = A + *g_srcPtr + (P & FLAG_CARRY);
        A = (uint8_t)temp;
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, temp > 0xFF);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, (uint8_t)(temp & 0x80) != (A & 0x80));
        checkNegative(temp);
        checkZero(temp);
    }

    void DEC()
    {
        --*g_srcPtr;
        checkNegative(*g_srcPtr);
        checkZero(*g_srcPtr);
    }

    void DEX()
    {
        --X;
        checkNegative(X);
        checkZero(X);
    }

    void DEY()
    {
        --Y;
        checkNegative(Y);
        checkZero(Y);
    }

    void INC()
    {
        ++*g_srcPtr;
        checkNegative(*g_srcPtr);
        checkZero(*g_srcPtr);
    }

    void INX()
    {
        ++X;
        checkNegative(X);
        checkZero(X);
    }

    void INY()
    {
        ++Y;
        checkNegative(Y);
        checkZero(Y);
    }

    void SBC()
    {
        A += (*g_srcPtr ^ 0xFF) + (P & FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, A > 0x7F);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, A >= 0);
        checkNegative(A);
        checkZero(A);
    }


    //--Bitwise--
    void AND()
    {
        A &= *g_srcPtr;
        checkNegative(A);
        checkZero(A);
    }

    void ASL()
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, *g_srcPtr & 0x80);
        *g_srcPtr <<= 1;
        checkNegative(*g_srcPtr);
        checkZero(*g_srcPtr);
    }

    void BIT() 
    {
        uint8_t temp = A & *g_srcPtr;
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, temp & 0x40);
        checkNegative(temp);
        checkZero(temp);
    }

    void EOR()
    {
        A ^= *g_srcPtr;
        checkNegative(A);
        checkZero(A);
    }

    void LSR()
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, *g_srcPtr & 0x01);
        *g_srcPtr >>= 1;
        P = setBits(P, (uint8_t)StatusFlags::FLAG_NEGATIVE, false); //Clear negative flag
        checkZero(*g_srcPtr);
    }

    void ORA()
    {
        A |= *g_srcPtr;
        checkNegative(A);
        checkZero(A);
    }

    void ROL()
    {
        uint8_t temp = setBits(*g_srcPtr << 1, 0x01, P & StatusFlags::FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, *g_srcPtr & 0x80);
        *g_srcPtr = temp;
        checkNegative(*g_srcPtr);
        checkZero(*g_srcPtr);
    }

    void ROR()
    {
        uint8_t temp = setBits(*g_srcPtr >> 1, 0x80, P & StatusFlags::FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, *g_srcPtr & 0x01);
        *g_srcPtr = temp;
        checkNegative(*g_srcPtr);
        checkZero(*g_srcPtr);
    }


    //--Branch--
    void BCS()
    {
        if (P & FLAG_CARRY) {
            PC = --PC + *(int8_t*)g_srcPtr;
        }
    }

    void BCC()
    {
        if (!(P & FLAG_CARRY)) {
            PC = --PC + *(int8_t*)g_srcPtr;
        }
    }

    void BEQ()
    {
        if (P & FLAG_ZERO) {
            PC = --PC + *(int8_t*)g_srcPtr;
        }
    }

    void BNE()
    {
        if (!(P & FLAG_ZERO)) {
            PC = --PC + *(int8_t*)g_srcPtr;
        }
    }

    void BMI()
    {
        if (P & FLAG_NEGATIVE) {
            PC = --PC + *(int8_t*)g_srcPtr;
        }
    }

    void BPL()
    {
        if (!(P & FLAG_NEGATIVE)) {
            PC = --PC + *(int8_t*)g_srcPtr;
        }
    }

    void BVS()
    {
        if (P & FLAG_OVERFLOW) {
            PC = --PC + *(int8_t*)g_srcPtr;
        }
    }

    void BVC()
    {
        if (!(P & FLAG_OVERFLOW)) {
            PC = --PC + *(int8_t*)g_srcPtr;
        }
    }


    //--Jump--
    void JMP()
    {
        PC = *(uint16_t*)g_srcPtr;
    }

    void JSR()
    {
        push16(PC); //Push next instruction
        PC = *(uint16_t*)g_srcPtr;
    }

    void RTI()
    {
        P  = pull8();
        PC = pull16();
    }

    void RTS()
    {
        PC = pull16();
    }


    //--Registers--
    void CLC()
    {
        P &= ~StatusFlags::FLAG_CARRY;
    }

    void CLD()
    {
        P &= ~StatusFlags::FLAG_DECIMAL_MODE;
    }

    void CLI()
    {
        P &= ~StatusFlags::FLAG_INTERRUPT_DISABLE;
    }

    void CLV()
    {
        P &= ~StatusFlags::FLAG_OVERFLOW;
    }

    void CMP()
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, A >= *g_srcPtr);
        checkNegative(A - *g_srcPtr);
        checkZero(A - *g_srcPtr);
    }

    void CPX()
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, X >= *g_srcPtr);
        checkNegative(X - *g_srcPtr);
        checkZero(X - *g_srcPtr);
    }

    void CPY()
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, Y >= *g_srcPtr);
        checkNegative(Y - *g_srcPtr);
        checkZero(Y - *g_srcPtr);
    }

    void SEC()
    {
        P |= StatusFlags::FLAG_CARRY;
    }

    void SED()
    {
        P |= StatusFlags::FLAG_DECIMAL_MODE;
    }

    void SEI()
    {
        P |= StatusFlags::FLAG_INTERRUPT_DISABLE;
    }


    //--Stack--
    void PHA()
    {
        push8(A);
    }

    void PHP()
    {
        push8(P);
    }

    void PLA()
    {
        A = pull8();
        checkNegative(A);
        checkZero(A);
    }

    void PLP()
    {
        P = pull8();
    }


    //--System--
    void BRK()
    {
        //Waist cycle ? (or set interrupt flag ?)
    }

    void NOP()
    {
        //Waist cycle
    }




    //Debugging
    void enableCpuLog()
    {
        g_cpuLogEnabled = true;
    }

    void disableCpuLog()
    {
        g_cpuLogEnabled = false;
    }

    void setCpuLogStream(std::ostream& logStream)
    {
        g_cpuLogStream = &logStream;
    }

    void printCpuLog()
    {
        *g_cpuLogStream << std::hex
                        << "A: "   << A       << " "
                        << "X: "   << X       << " "
                        << "Y: "   << Y       << " "
                        << "P: "   << P       << " "
                        << "SP: "  << SP      << " "
                        << "CYC: " << g_ticks << std::endl;
    }

}

