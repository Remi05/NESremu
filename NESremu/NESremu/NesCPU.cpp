#include "NesCpu.h"


namespace NESremu
{
    //Tables
    NesCpu::AddressingMode NesCpu::AddrModesTable[256] = {
        /* 0xVH  0     1     2    3    4    5    6    7    8    9     A    B    C     D     E     F  */
        /* 0 */  &imp,  &indx, &imp, &imp, &imp, &zp,  &zp,  &imp, &imp, &imm,  &acc, &imp, &imp,  &absl, &absl, &imp,
        /* 1 */  &rel,  &indy, &imp, &imp, &imp, &zpx, &zpx, &imp, &imp, &absy, &imp, &imp, &imp,  &absx, &absx, &imp,
        /* 2 */  &absl, &indx, &imp, &imp, &zp,  &zp,  &zp,  &imp, &imp, &imm,  &acc, &imp, &absl, &absl, &absl, &imp,
        /* 3 */  &rel,  &indy, &imp, &imp, &imp, &zpx, &zpx, &imp, &imp, &absy, &imp, &imp, &imp,  &absx, &absx, &imp,
        /* 4 */  &imp,  &indx, &imp, &imp, &imp, &zp,  &zp,  &imp, &imp, &imm,  &acc, &imp, &absl, &absl, &absl, &imp,
        /* 5 */  &rel,  &indy, &imp, &imp, &imp, &zpx, &zpx, &imp, &imp, &absy, &imp, &imp, &imp,  &absx, &absx, &imp,
        /* 6 */  &imp,  &indx, &imp, &imp, &imp, &zp,  &zp,  &imp, &imp, &imm,  &acc, &imp, &ind,  &absl, &absl, &imp,
        /* 7 */  &rel,  &indy, &imp, &imp, &imp, &zpx, &zpx, &imp, &imp, &absy, &imp, &imp, &imp,  &absx, &absx, &imp,
        /* 8 */  &imp,  &indx, &imp, &imp, &zp,  &zp,  &zp,  &imp, &imp, &imp,  &imp, &imp, &absl, &absl, &absl, &imp,
        /* 9 */  &rel,  &indy, &imp, &imp, &zpx, &zpx, &zpy, &imp, &imp, &absy, &imp, &imp, &imp,  &absx, &imp,  &imp,
        /* A */  &imm,  &indx, &imm, &imp, &zp,  &zp,  &zp,  &imp, &imp, &imm,  &imp, &imp, &absl, &absl, &absl, &imp,
        /* B */  &rel,  &indy, &imp, &imp, &zpx, &zpx, &zpy, &imp, &imp, &absy, &imp, &imp, &absx, &absx, &absy, &imp,
        /* C */  &imm,  &indx, &imp, &imp, &zp,  &zp,  &zp,  &imp, &imp, &imm,  &imp, &imp, &absl, &absl, &absl, &imp,
        /* D */  &rel,  &indy, &imp, &imp, &imp, &zpx, &zpx, &imp, &imp, &absy, &imp, &imp, &imp,  &absx, &absx, &imp,
        /* E */  &imm,  &indx, &imp, &imp, &zp,  &zp,  &zp,  &imp, &imp, &imm,  &imp, &imp, &absl, &absl, &absl, &imp,
        /* F */  &rel,  &indy, &imp, &imp, &imp, &zpx, &zpx, &imp, &imp, &absy, &imp, &imp, &imp,  &absx, &absx, &imp };

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


    NesCpu::Opcode NesCpu::OpcodesTable[256] = {
        /* 0xVH  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F  */
        /* 0 */ &brk, &ora, &nop, &nop, &nop, &ora, &asl, &nop, &php, &ora, &asl, &nop, &nop, &ora, &asl, &nop,
        /* 1 */ &bpl, &ora, &nop, &nop, &nop, &ora, &asl, &nop, &clc, &ora, &nop, &nop, &nop, &ora, &asl, &nop,
        /* 2 */ &jsr, &AND, &nop, &nop, &bit, &AND, &rol, &nop, &plp, &AND, &rol, &nop, &bit, &AND, &rol, &nop,
        /* 3 */ &bmi, &AND, &nop, &nop, &nop, &AND, &rol, &nop, &sec, &AND, &nop, &nop, &nop, &AND, &rol, &nop,
        /* 4 */ &rti, &eor, &nop, &nop, &nop, &eor, &lsr, &nop, &pha, &eor, &lsr, &nop, &jmp, &eor, &lsr, &nop,
        /* 5 */ &bvc, &eor, &nop, &nop, &nop, &eor, &lsr, &nop, &cli, &eor, &nop, &nop, &nop, &eor, &lsr, &nop,
        /* 6 */ &rts, &adc, &nop, &nop, &nop, &adc, &ror, &nop, &pla, &adc, &ror, &nop, &jmp, &adc, &ror, &nop,
        /* 7 */ &bvs, &adc, &nop, &nop, &nop, &adc, &ror, &nop, &sei, &adc, &nop, &nop, &nop, &adc, &ror, &nop,
        /* 8 */ &nop, &sta, &nop, &nop, &sty, &sta, &stx, &nop, &dey, &nop, &txa, &nop, &sty, &sta, &stx, &nop,
        /* 9 */ &bcc, &sta, &nop, &nop, &sty, &sta, &stx, &nop, &tya, &sta, &txs, &nop, &nop, &sta, &nop, &nop,
        /* A */ &ldy, &lda, &ldx, &nop, &ldy, &lda, &ldx, &nop, &tay, &lda, &tax, &nop, &ldy, &lda, &ldx, &nop,
        /* B */ &bcs, &lda, &nop, &nop, &ldy, &lda, &ldx, &nop, &clv, &lda, &tsx, &nop, &ldy, &lda, &ldx, &nop,
        /* C */ &cpy, &cmp, &nop, &nop, &cpy, &cmp, &dec, &nop, &iny, &cmp, &dex, &nop, &cpy, &cmp, &dec, &nop,
        /* D */ &bne, &cmp, &nop, &nop, &nop, &cmp, &dec, &nop, &cld, &cmp, &nop, &nop, &nop, &cmp, &dec, &nop,
        /* E */ &cpx, &sbc, &nop, &nop, &cpx, &sbc, &inc, &nop, &inx, &sbc, &nop, &nop, &cpx, &sbc, &inc, &nop,
        /* F */ &beq, &sbc, &nop, &nop, &nop, &sbc, &inc, &nop, &sed, &sbc, &nop, &nop, &nop, &sbc, &inc, &nop };

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

    uint32_t NesCpu::TicksTable[256] = {
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
    void NesCpu::init()
    {

    }

    void NesCpu::reset()
    {

    }

    void NesCpu::shutdown()
    {

    }

    void NesCpu::tick()
    {
        uint8_t opcode = Memory[PC];
        (this->*AddrModesTable[opcode])();
        (this->*OpcodesTable[opcode])();
        m_ticks += TicksTable[opcode] + m_tickOffset;
        //...

        //Debugging
        if (m_logEnabled) {
            printLog();
        }
    }


    //Debugging
    void NesCpu::enableLog()
    {
        m_logEnabled = true;
    }

    void NesCpu::disableLog()
    {
        m_logEnabled = false;
    }

    void NesCpu::printLog()
    {
        *m_logStream << std::hex
            << "A: " << A << " "
            << "X: " << X << " "
            << "Y: " << Y << " "
            << "P: " << P << " "
            << "SP: " << SP << " "
            << "CYC: " << m_ticks << std::endl;
    }

    void NesCpu::setLogStream(std::ostream& logStream)
    {
        m_logStream = &logStream;
    }


    //template<class T>
    //T memRead(uint8_t* memPtr)
    //{
    //    //Handle I/O
    //    //Handle I/O
    //    if (memPtr >= InternalRAM && memPtr < InternalRAM + INTERNAL_RAM_SIZE) {
    //        //Internal RAM mirroring
    //    }
    //    else if (memPtr >= PpuRegisters && memPtr < PpuRegisters + PPU_REGISTERS_SIZE) {
    //        //PPU registers mirroring and PPU I/O
    //    }
    //    else if (memPtr == DmaSpriteMem) {
    //        //Sprite memory DMA
    //    }
    //    else if (memPtr == Controller1) {
    //        //Controller #1 I/O
    //    }
    //    else if (memPtr == Controller2) {
    //        //Controller #2 I/O
    //    }
    //    else if (memPtr >= ApuRegisters && memPtr < ApuRegisters + APU_REGISTERS_SIZE) {
    //        //APU I/O (MemSpriteDMA, Controller1 and Controller2 are checked before)
    //    }
    //    else {
    //        //Basic read
    //    }
    //    return *(T*)memPtr; //Basic read, move into condition
    //}

    //void memWrite(uint8_t* memPtr, uint8_t value)
    //{
    //    //Handle I/O
    //    if (memPtr >= InternalRAM && memPtr < InternalRAM + INTERNAL_RAM_SIZE) {
    //        //Internal RAM mirroring
    //    }
    //    else if (memPtr >= PpuRegisters && memPtr < PpuRegisters + PPU_REGISTERS_SIZE) {
    //        //PPU registers mirroring and PPU I/O
    //    }
    //    else if (memPtr == DmaSpriteMem) {
    //        //Sprite memory DMA
    //    }
    //    else if (memPtr == Controller1) {
    //        //Controller #1 I/O
    //    }
    //    else if (memPtr == Controller2) {
    //        //Controller #2 I/O
    //    }
    //    else if (memPtr >= ApuRegisters && memPtr < ApuRegisters + APU_REGISTERS_SIZE) {
    //        //APU I/O (MemSpriteDMA, Controller1 and Controller2 are checked before)
    //    }
    //    else {
    //        *memPtr = value; //Basic write
    //    }
    //}


    //Flags related functions
    void NesCpu::checkNegative(uint16_t val)
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_ZERO, val & 0x80);
    }

    void NesCpu::checkZero(uint16_t val)
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_ZERO, val == 0);
    }


    //Stack operations
    uint8_t  NesCpu::pull8()
    {
        return Stack[++SP];
    }

    uint16_t NesCpu::pull16()
    {
        return *((uint16_t*)Stack + (SP += 2));
    }

    void NesCpu::push8(uint8_t value)
    {
        Stack[SP--] = value;
    }

    void NesCpu::push16(uint16_t value)
    {
        //Check if good byte order
        *((uint16_t*)Stack + SP) = value;
        SP -= 2;
    }



    //Addressing modes

    //TO DO: Add tick offset.

    void NesCpu::absl()
    {
        m_srcPtr = Memory + *((uint16_t*)(Memory + PC));
        PC += 2;
    }

    void NesCpu::absx()
    {
        m_srcPtr = Memory + *((uint16_t*)(Memory + PC)) + X;
        PC += 2;
    }

    void NesCpu::absy()
    {
        m_srcPtr = Memory + *((uint16_t*)(Memory + PC)) + Y;
        PC += 2;
    }

    void NesCpu::acc()
    {
        m_srcPtr = &A;
    }

    void NesCpu::imm()
    {
        m_srcPtr = Memory + PC++;
    }

    void NesCpu::imp() { }

    void NesCpu::ind()
    {
        m_srcPtr = Memory + PC;
        PC += 2;
    }

    void NesCpu::indx()
    {
        uint16_t tmpAddr = Memory[(Memory[PC] + X) & 0x00FF] | (Memory[(Memory[PC++] + X + 1) & 0x00FF] << 8);
        m_srcPtr = Memory + tmpAddr;
    }

    void NesCpu::indy()
    {
        uint16_t tmpAddr = Memory[Memory[PC]] | (Memory[(Memory[PC++] + 1) & 0x00FF] << 8);
        m_srcPtr = Memory + tmpAddr + Y;
    }

    void NesCpu::rel()
    {
        m_srcPtr = Memory + PC++;
    }

    void NesCpu::zp()
    {
        m_srcPtr = Memory + Memory[PC++];
    }

    void NesCpu::zpx()
    {
        m_srcPtr = Memory + ((Memory[PC++] + X) & 0x00FF);
    }

    void NesCpu::zpy()
    {
        m_srcPtr = Memory + ((Memory[PC++] + Y) & 0x00FF);
    }



    //Opcodes

    //--Storage--
    void NesCpu::lda()
    {
        A = *m_srcPtr; //A = memRead<uint8_t>(g_srcPtr);
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::ldx()
    {
        X = *m_srcPtr; //X = memRead<uint8_t>(g_srcPtr);
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::ldy()
    {
        Y = *m_srcPtr; //Y = memRead<uint8_t>(g_srcPtr);
        checkNegative(Y);
        checkZero(Y);
    }

    void NesCpu::sta()
    {
        *m_srcPtr = A; //memWrite(g_srcPtr, A)
    }

    void NesCpu::stx()
    {
        *m_srcPtr = X; //memWrite(g_srcPtr, X)
    }

    void NesCpu::sty()
    {
        *m_srcPtr = Y; //memWrite(g_srcPtr, Y)
    }

    void NesCpu::tax()
    {
        X = A;
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::tay()
    {
        Y = A;
        checkNegative(Y);
        checkZero(Y);
    }

    void NesCpu::txa()
    {
        A = X;
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::tya()
    {
        A = Y;
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::tsx()
    {
        X = SP;
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::txs()
    {
        SP = X;
        checkNegative(SP);
        checkZero(SP);
    }


    //--Math--
    void NesCpu::adc()
    {
        uint16_t tmp = A + *m_srcPtr + (P & FLAG_CARRY); //uint16_t tmp = A + memRead<uint8_t>(g_srcPtr) + (P & FLAG_CARRY);
        A = (uint8_t)tmp;
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, tmp > 0xFF);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, (uint8_t)(tmp & 0x80) != (A & 0x80));
        checkNegative(tmp);
        checkZero(tmp);
    }

    void NesCpu::dec()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //--arg;
        //memWrite(g_srcPtr, arg);
        //checkNegative(arg);
        //checkZero(arg);
        --*m_srcPtr; 
        checkNegative(*m_srcPtr);
        checkZero(*m_srcPtr);
    }

    void NesCpu::dex()
    {
        --X;
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::dey()
    {
        --Y;
        checkNegative(Y);
        checkZero(Y);
    }

    void NesCpu::inc()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //++arg;
        //memWrite(g_srcPtr, arg);
        //checkNegative(arg);
        //checkZero(arg);
        ++*m_srcPtr;
        checkNegative(*m_srcPtr);
        checkZero(*m_srcPtr);
    }

    void NesCpu::inx()
    {
        ++X;
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::iny()
    {
        ++Y;
        checkNegative(Y);
        checkZero(Y);
    }

    void NesCpu::sbc()
    {
        A += (*m_srcPtr ^ 0xFF) + (P & FLAG_CARRY); //A += (memRead<uint8_t>(g_srcPtr) ^ 0xFF) + (P & FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, A > 0x7F);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, A >= 0);
        checkNegative(A);
        checkZero(A);
    }


    //--Bitwise--
    void NesCpu::AND()
    {
        A &= *m_srcPtr; //A &= memRead<uint8_t>(g_srcPptr)
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::asl()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, arg & 0x80);
        //arg <<= 1;
        //memWrite(g_srcPtr, arg);
        //checkNegative(arg);
        //checkZero(arg);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, *m_srcPtr & 0x80);
        *m_srcPtr <<= 1;
        checkNegative(*m_srcPtr);
        checkZero(*m_srcPtr);
    }

    void NesCpu::bit()
    {
        uint8_t tmp = A & *m_srcPtr; //uint8_t tmp = A & memRead<uint8_t>(g_srcPtr);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, tmp & 0x40);
        checkNegative(tmp);
        checkZero(tmp);
    }

    void NesCpu::eor()
    {
        A ^= *m_srcPtr; //A ^= memRead<uint8_t>(g_srcPptr)
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::lsr()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, arg & 0x80);
        //arg >>= 1;
        //memWrite(g_srcPtr, arg);
        //P = setBits(P, (uint8_t)StatusFlags::FLAG_NEGATIVE, false);
        //checkZero(arg);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, *m_srcPtr & 0x01);
        *m_srcPtr >>= 1;
        P = setBits(P, (uint8_t)StatusFlags::FLAG_NEGATIVE, false); //Clear negative flag
        checkZero(*m_srcPtr);
    }

    void NesCpu::ora()
    {
        A |= *m_srcPtr; //A |= memRead<uint8_t>(g_srcPtr);
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::rol()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //uint8_t tmp = setBits(arg << 1, 0x01, P & StatusFlags::FLAG_CARRY);
        //P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, arg & 0x80);
        //arg = tmp;
        //memWrite(g_srcPtr, arg);
        //checkNegative(arg);
        //checkZero(arg);
        uint8_t tmp = setBits(*m_srcPtr << 1, 0x01, P & StatusFlags::FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, *m_srcPtr & 0x80);
        *m_srcPtr = tmp;
        checkNegative(*m_srcPtr);
        checkZero(*m_srcPtr);
    }

    void NesCpu::ror()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //uint8_t tmp = setBits(arg >> 1, 0x80, P & StatusFlags::FLAG_CARRY);
        //P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, arg & 0x01);
        //arg = tmp;
        //memWrite(g_srcPtr, arg);
        //checkNegative(arg);
        //checkZero(arg);
        uint8_t tmp = setBits(*m_srcPtr >> 1, 0x80, P & StatusFlags::FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, *m_srcPtr & 0x01);
        *m_srcPtr = tmp;
        checkNegative(*m_srcPtr);
        checkZero(*m_srcPtr);
    }


    //--Branch--
    void NesCpu::bcs()
    {
        if (P & FLAG_CARRY) {
            PC = --PC + *(int8_t*)m_srcPtr; //PC = --PC + memRead<int8_t>(g_srcPtr);
        }
    }

    void NesCpu::bcc()
    {
        if (!(P & FLAG_CARRY)) {
            PC = --PC + *(int8_t*)m_srcPtr; //PC = --PC + memRead<int8_t>(g_srcPtr);
        }
    }

    void NesCpu::beq()
    {
        if (P & FLAG_ZERO) {
            PC = --PC + *(int8_t*)m_srcPtr; //PC = --PC + memRead<int8_t>(g_srcPtr);
        }
    }

    void NesCpu::bne()
    {
        if (!(P & FLAG_ZERO)) {
            PC = --PC + *(int8_t*)m_srcPtr; //PC = --PC + memRead<int8_t>(g_srcPtr);
        }
    }

    void NesCpu::bmi()
    {
        if (P & FLAG_NEGATIVE) {
            PC = --PC + *(int8_t*)m_srcPtr; //PC = --PC + memRead<int8_t>(g_srcPtr);
        }
    }

    void NesCpu::bpl()
    {
        if (!(P & FLAG_NEGATIVE)) {
            PC = --PC + *(int8_t*)m_srcPtr; //PC = --PC + memRead<int8_t>(g_srcPtr);
        }
    }

    void NesCpu::bvs()
    {
        if (P & FLAG_OVERFLOW) {
            PC = --PC + *(int8_t*)m_srcPtr; //PC = --PC + memRead<int8_t>(g_srcPtr);
        }
    }

    void NesCpu::bvc()
    {
        if (!(P & FLAG_OVERFLOW)) {
            PC = --PC + *(int8_t*)m_srcPtr; //PC = --PC + memRead<int8_t>(g_srcPtr);
        }
    }


    //--Jump--
    void NesCpu::jmp()
    {
        PC = *(uint16_t*)m_srcPtr; //PC = memRead<uint16_t>(g_srcPtr);
    }

    void NesCpu::jsr()
    {
        push16(PC); //Push next instruction
        PC = *(uint16_t*)m_srcPtr; //PC = memRead<uint16_t>(g_srcPtr);
    }

    void NesCpu::rti()
    {
        P  = pull8();
        PC = pull16();
    }

    void NesCpu::rts()
    {
        PC = pull16();
    }


    //--Registers--
    void NesCpu::clc()
    {
        P &= ~StatusFlags::FLAG_CARRY;
    }

    void NesCpu::cld()
    {
        P &= ~StatusFlags::FLAG_DECIMAL_MODE;
    }

    void NesCpu::cli()
    {
        P &= ~StatusFlags::FLAG_INTERRUPT_DISABLE;
    }

    void NesCpu::clv()
    {
        P &= ~StatusFlags::FLAG_OVERFLOW;
    }

    void NesCpu::cmp()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, A >= arg);
        //checkNegative(A - arg);
        //checkZero(A - arg);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, A >= *m_srcPtr);
        checkNegative(A - *m_srcPtr);
        checkZero(A - *m_srcPtr);
    }

    void NesCpu::cpx()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, X >= arg);
        //checkNegative(X - arg);
        //checkZero(X - arg);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, X >= *m_srcPtr);
        checkNegative(X - *m_srcPtr);
        checkZero(X - *m_srcPtr);
    }

    void NesCpu::cpy()
    {
        //uint8_t arg = memRead<uint8_t>(g_srcPtr);
        //P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, Y >= arg);
        //checkNegative(Y - arg);
        //checkZero(Y - arg);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, Y >= *m_srcPtr);
        checkNegative(Y - *m_srcPtr);
        checkZero(Y - *m_srcPtr);
    }

    void NesCpu::sec()
    {
        P |= StatusFlags::FLAG_CARRY;
    }

    void NesCpu::sed()
    {
        P |= StatusFlags::FLAG_DECIMAL_MODE;
    }

    void NesCpu::sei()
    {
        P |= StatusFlags::FLAG_INTERRUPT_DISABLE;
    }


    //--Stack--
    void NesCpu::pha()
    {
        push8(A);
    }

    void NesCpu::php()
    {
        push8(P);
    }

    void NesCpu::pla()
    {
        A = pull8();
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::plp()
    {
        P = pull8();
    }


    //--System--
    void NesCpu::brk()
    {
        //Waist cycle ? (or set interrupt flag ?)
    }

    void NesCpu::nop()
    {
        //Waist cycle
    }

}

