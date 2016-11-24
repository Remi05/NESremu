#include "NesCpu.h"


namespace nesremu
{
    //Tables
    NesCpu::AddressingMode NesCpu::AddrModesTable[256] = {
        /* 0xVH  0      1      2     3     4     5     6     7     8     9      A     B     C      D      E      F  */
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


    NesCpu::Opcode NesCpu::OpcodesTable[256] = {
        /* 0xVH 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F  */
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


    //Constructor and destructor
    NesCpu::NesCpu(NesBus* bus)
        :m_bus(bus) {}

    NesCpu::~NesCpu() {}


    //Core CPU functions
    uint32_t NesCpu::getTicks()
    {
        return m_ticks;
    }

    void NesCpu::reset()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "CPU:\t Resetting..." << std::endl;
        }
    }

    void NesCpu::start() 
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "CPU:\t Starting..." << std::endl;
        }
    }

    void NesCpu::stop()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "CPU:\t Stopping..." << std::endl;
        }
    }

    void NesCpu::tick()
    {
        handleInterrupts(); //Handle interrupts that occured between ticks.
        uint8_t  opcode  = m_bus->read(PC); //Fetch opcode.
        uint16_t address = (this->*AddrModesTable[opcode])(); //Fetch argument address based on addessing mode.
        (this->*OpcodesTable[opcode])(address); //Execute the instruction.
        handleInterrupts(); //Handle interrupts caused by the instruction.
        m_ticks += TicksTable[opcode] + m_tickOffset; //Update the ticks count.
        //...

        //Debugging
        if (m_logEnabled) {
            *m_logStream << std::hex
                         << "A: "   << A  << "  "
                         << "X: "   << X  << "  "
                         << "Y: "   << Y  << "  "
                         << "P: "   << P  << "  "
                         << "SP: "  << SP << "  "
                         << "CYC: " << m_ticks << std::endl;
        }
    }


    //Saving
    void NesCpu::load(std::istream& saveStream)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "CPU:\t Loading..." << std::endl;
        }

        //Load the registers from the save stream.
        saveStream.read((char*)&PC, sizeof(PC));
        saveStream.read((char*)&SP, sizeof(SP));
        saveStream.read((char*)&A, sizeof(A));
        saveStream.read((char*)&X, sizeof(X));
        saveStream.read((char*)&Y, sizeof(Y));
        saveStream.read((char*)&P, sizeof(P));
        //Load the tick count from the save stream.
        saveStream.read((char*)&m_ticks, sizeof(m_ticks));
    }

    void NesCpu::save(std::ostream& saveStream)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "CPU:\t Saving..." << std::endl;
        }

        //Write the registers to the save stream.
        saveStream.write((char*)&PC, sizeof(PC));
        saveStream.write((char*)&SP, sizeof(SP));
        saveStream.write((char*)&A, sizeof(A));
        saveStream.write((char*)&X, sizeof(X));
        saveStream.write((char*)&Y, sizeof(Y));
        saveStream.write((char*)&P, sizeof(P));
        //Write the tick count to the save stream.
        saveStream.write((char*)&m_ticks, sizeof(m_ticks));
    }


    //Flags related functions
    void NesCpu::checkNegative(uint16_t val)
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_ZERO, val & 0x80);
    }

    void NesCpu::checkZero(uint16_t val)
    {
        P = setBits(P, (uint8_t)StatusFlags::FLAG_ZERO, val == 0);
    }


    //Reading
    uint16_t NesCpu::read16(uint16_t address)
    {
        uint16_t low  = m_bus->read(address);
        uint16_t high = m_bus->read(++address);
        return (high << 8) | low;
    }


    //Stack operations
    uint8_t  NesCpu::pull8()
    {
        return m_bus->read(STACK_ADDRESS + ++SP);
    }

    uint16_t NesCpu::pull16()
    {
        uint16_t low  = m_bus->read(STACK_ADDRESS + ++SP);
        uint16_t high = m_bus->read(STACK_ADDRESS + ++SP);
        return (high << 8) | low;
    }

    void NesCpu::push8(uint8_t value)
    {
        return m_bus->write(STACK_ADDRESS + SP--, value);
    }

    void NesCpu::push16(uint16_t value)
    {
        m_bus->write(STACK_ADDRESS + SP--, value >> 8);
        m_bus->write(STACK_ADDRESS + SP--, value & 0xFF);
    }


    //Branching
    void NesCpu::branch(uint16_t off_address)
    {
        PC += (int8_t)m_bus->read(off_address);
    }


    //Interrupts
    void NesCpu::irq() {}

    void NesCpu::nmi() {}

    void NesCpu::handleInterrupts() {}



    //Addressing modes

    //TO DO: Add tick offset.

    uint16_t NesCpu::absl()
    {
        uint16_t address = read16(PC);
        PC += 2;
        m_isAccumulatorMode = false;
        return address;
    }

    uint16_t NesCpu::absx()
    {
        uint16_t address = read16(PC) + X;
        PC += 2;
        m_isAccumulatorMode = false;
        return address;
    }

    uint16_t NesCpu::absy()
    {
        uint16_t address = read16(PC) + Y;
        PC += 2;
        m_isAccumulatorMode = false;
        return address;
    }

    uint16_t NesCpu::acc()
    {
        m_isAccumulatorMode = true;
        //The address is not used in the accumulator
        //addressing mode so we return a dummy address.
        return 0;
    }

    uint16_t NesCpu::imm()
    {
        m_isAccumulatorMode = false;
        return PC++;
    }

    uint16_t NesCpu::imp() 
    {
        //The address is not used in the implied
        //addressing mode so we return a dummy address.
        return 0;
    }

    uint16_t NesCpu::ind()
    {
        uint16_t address = PC;
        PC += 2;
        m_isAccumulatorMode = false;
        return address;
    }

    uint16_t NesCpu::indx()
    {
        uint16_t arg = read16(PC);       
        uint16_t address = m_bus->read((arg + X) & 0x00FF) | (m_bus->read((arg + X + 1) & 0x00FF) << 8);
        PC += 2;
        m_isAccumulatorMode = false;
        return address;
    }

    uint16_t NesCpu::indy()
    {
        uint16_t arg = read16(PC);
        uint16_t address = (m_bus->read(arg) | (m_bus->read((arg + 1) & 0x00FF) << 8)) + Y;
        PC += 2;
        m_isAccumulatorMode = false;
        return address;
    }

    uint16_t NesCpu::rel()
    {
        m_isAccumulatorMode = false;
        return PC;
    }

    uint16_t NesCpu::zp()
    {
        m_isAccumulatorMode = false;
        return m_bus->read(PC++);
    }

    uint16_t NesCpu::zpx()
    {
        m_isAccumulatorMode = false;
        return (m_bus->read(PC++) + X) & 0x00FF;
    }

    uint16_t NesCpu::zpy()
    {
        m_isAccumulatorMode = false;
        return (m_bus->read(PC++) + Y) & 0x00FF;
    }



    //Opcodes

    //--Storage--
    void NesCpu::lda(uint16_t address)
    {
        A = m_bus->read(address);
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::ldx(uint16_t address)
    {
        X = m_bus->read(address);
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::ldy(uint16_t address)
    {
        Y = m_bus->read(address);
        checkNegative(Y);
        checkZero(Y);
    }

    void NesCpu::sta(uint16_t address)
    {
        m_bus->write(address, A);
    }

    void NesCpu::stx(uint16_t address)
    {
        m_bus->write(address, X);
    }

    void NesCpu::sty(uint16_t address)
    {
        m_bus->write(address, Y);
    }

    void NesCpu::tax(uint16_t address)
    {
        X = A;
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::tay(uint16_t address)
    {
        Y = A;
        checkNegative(Y);
        checkZero(Y);
    }

    void NesCpu::txa(uint16_t address)
    {
        A = X;
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::tya(uint16_t address)
    {
        A = Y;
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::tsx(uint16_t address)
    {
        X = SP;
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::txs(uint16_t address)
    {
        SP = X;
        checkNegative(SP);
        checkZero(SP);
    }


    //--Math--
    void NesCpu::adc(uint16_t address)
    {
        uint16_t tmp = A + m_bus->read(address) + (P & StatusFlags::FLAG_CARRY);
        A = (uint8_t)tmp;
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, tmp > 0xFF);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, (uint8_t)(tmp & 0x80) != (A & 0x80));
        checkNegative(tmp);
        checkZero(tmp);
    }

    void NesCpu::dec(uint16_t address)
    {
        uint8_t arg = m_bus->read(address);
        --arg;
        m_bus->write(address, arg);
        checkNegative(arg);
        checkZero(arg);
    }

    void NesCpu::dex(uint16_t address)
    {
        --X;
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::dey(uint16_t address)
    {
        --Y;
        checkNegative(Y);
        checkZero(Y);
    }

    void NesCpu::inc(uint16_t address)
    {
        uint8_t arg = m_bus->read(address);
        ++arg;
        m_bus->write(address, arg);
        checkNegative(arg);
        checkZero(arg);
    }

    void NesCpu::inx(uint16_t address)
    {
        ++X;
        checkNegative(X);
        checkZero(X);
    }

    void NesCpu::iny(uint16_t address)
    {
        ++Y;
        checkNegative(Y);
        checkZero(Y);
    }

    void NesCpu::sbc(uint16_t address)
    {
        A += (m_bus->read(address) ^ 0xFF) + (P & StatusFlags::FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, A > 0x7F);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, A >= 0);
        checkNegative(A);
        checkZero(A);
    }


    //--Bitwise--
    void NesCpu::AND(uint16_t address)
    {
        A &= m_bus->read(address);
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::asl(uint16_t address)
    {
        uint8_t arg = m_isAccumulatorMode ? A : m_bus->read(address);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, arg & 0x80);
        arg <<= 1;
        if (m_isAccumulatorMode) {
            A = arg;
        }
        else {
            m_bus->write(address, arg);
        }
        checkNegative(arg);
        checkZero(arg);
    }

    void NesCpu::bit(uint16_t address)
    {
        uint8_t tmp = A & m_bus->read(address);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_OVERFLOW, tmp & 0x40);
        checkNegative(tmp);
        checkZero(tmp);
    }

    void NesCpu::eor(uint16_t address)
    {
        A ^= m_bus->read(address);
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::lsr(uint16_t address)
    {
        uint8_t arg = m_isAccumulatorMode ? A : m_bus->read(address);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, arg & 0x01);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_NEGATIVE, false);
        arg >>= 1;
        if (m_isAccumulatorMode) {
            A = arg;
        }
        else {
            m_bus->write(address, arg);
        }
        checkZero(arg);
    }

    void NesCpu::ora(uint16_t address)
    {
        A |= m_bus->read(address);
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::rol(uint16_t address)
    {
        uint8_t arg = m_isAccumulatorMode ? A : m_bus->read(address);
        uint8_t tmp = setBits(arg << 1, 0x01, P & StatusFlags::FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, arg & 0x80);
        arg = tmp;
        if (m_isAccumulatorMode) {
            A = arg;
        }
        else {
            m_bus->write(address, arg);
        }
        checkNegative(arg);
        checkZero(arg);
    }

    void NesCpu::ror(uint16_t address)
    {
        uint8_t arg = m_isAccumulatorMode ? A : m_bus->read(address);
        uint8_t tmp = setBits(arg >> 1, 0x80, P & StatusFlags::FLAG_CARRY);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, arg & 0x01);
        arg = tmp;
        if (m_isAccumulatorMode) {
            A = arg;
        }
        else {
            m_bus->write(address, arg);
        }
        checkNegative(arg);
        checkZero(arg);
    }


    //--Branch--
    void NesCpu::bcs(uint16_t address)
    {
        if (P & FLAG_CARRY) {
            branch(address);
        }
    }

    void NesCpu::bcc(uint16_t address)
    {
        if (!(P & FLAG_CARRY)) {
            branch(address);
        }
    }

    void NesCpu::beq(uint16_t address)
    {
        if (P & FLAG_ZERO) {
            branch(address);
        }
    }

    void NesCpu::bne(uint16_t address)
    {
        if (!(P & FLAG_ZERO)) {
            branch(address);
        }
    }

    void NesCpu::bmi(uint16_t address)
    {
        if (P & FLAG_NEGATIVE) {
            branch(address);
        }
    }

    void NesCpu::bpl(uint16_t address)
    {
        if (!(P & FLAG_NEGATIVE)) {
            branch(address);
        }
    }

    void NesCpu::bvs(uint16_t address)
    {
        if (P & FLAG_OVERFLOW) {
            branch(address);
        }
    }

    void NesCpu::bvc(uint16_t address)
    {
        if (!(P & FLAG_OVERFLOW)) {
            branch(address);
        }
    }


    //--Jump--
    void NesCpu::jmp(uint16_t address)
    {
        PC = read16(address);
    }

    void NesCpu::jsr(uint16_t address)
    {
        push16(PC); //Push next instruction
        PC = read16(address);
    }

    void NesCpu::rti(uint16_t address)
    {
        P  = pull8();
        PC = pull16();
    }

    void NesCpu::rts(uint16_t address)
    {
        PC = pull16();
    }


    //--Registers--
    void NesCpu::clc(uint16_t address)
    {
        P &= ~StatusFlags::FLAG_CARRY;
    }

    void NesCpu::cld(uint16_t address)
    {
        P &= ~StatusFlags::FLAG_DECIMAL_MODE;
    }

    void NesCpu::cli(uint16_t address)
    {
        P &= ~StatusFlags::FLAG_INTERRUPT_DISABLE;
    }

    void NesCpu::clv(uint16_t address)
    {
        P &= ~StatusFlags::FLAG_OVERFLOW;
    }

    void NesCpu::cmp(uint16_t address)
    {
        uint8_t arg = m_bus->read(address);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, A >= arg);
        checkNegative(A - arg);
        checkZero(A - arg);
    }

    void NesCpu::cpx(uint16_t address)
    {
        uint8_t arg = m_bus->read(address);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, X >= arg);
        checkNegative(X - arg);
        checkZero(X - arg);
    }

    void NesCpu::cpy(uint16_t address)
    {
        uint8_t arg = m_bus->read(address);
        P = setBits(P, (uint8_t)StatusFlags::FLAG_CARRY, Y >= arg);
        checkNegative(Y - arg);
        checkZero(Y - arg);
    }

    void NesCpu::sec(uint16_t address)
    {
        P |= StatusFlags::FLAG_CARRY;
    }

    void NesCpu::sed(uint16_t address)
    {
        P |= StatusFlags::FLAG_DECIMAL_MODE;
    }

    void NesCpu::sei(uint16_t address)
    {
        P |= StatusFlags::FLAG_INTERRUPT_DISABLE;
    }


    //--Stack--
    void NesCpu::pha(uint16_t address)
    {
        push8(A);
    }

    void NesCpu::php(uint16_t address)
    {
        push8(P);
    }

    void NesCpu::pla(uint16_t address)
    {
        A = pull8();
        checkNegative(A);
        checkZero(A);
    }

    void NesCpu::plp(uint16_t address)
    {
        P = pull8();
    }


    //--System--
    void NesCpu::brk(uint16_t address)
    {
        push16(PC);
        push8(P);
        P |= StatusFlags::FLAG_BREAK;
        jmp(read16(BRK_VECTOR_ADDRESS));
    }

    void NesCpu::nop(uint16_t address)
    {
        //Waist cycle
    }

}

