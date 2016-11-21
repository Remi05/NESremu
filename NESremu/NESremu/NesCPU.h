#pragma once
#include <cstdint>
#include <iostream>
#include "NesBus.h"


namespace nesremu
{

    //Misc.
    template<class T>
    T setBits(T num, T mask, bool bitVal)
    {
        return bitVal ? num | mask : num & ~mask;
    }



    class NesCpu : public ILoggable
    {
    private:
        using AddressingMode = uint16_t(NesCpu::*)();
        using Opcode         = void(NesCpu::*)(uint16_t);

        //Memory constants
        static const uint16_t STACK_ADDRESS      = 0x0100;
        static const uint16_t BRK_VECTOR_ADDRESS = 0xFFFE;
        static const uint16_t INTERNAL_RAM_SIZE  = 0x1E00;
        static const uint16_t PPU_REGISTERS_SIZE = 0x2000;
        static const uint16_t APU_REGISTERS_SIZE = 0x0020;
        static const uint16_t EXPANSION_ROM_SIZE = 0x1FE0;
        static const uint16_t SAVE_RAM_SIZE      = 0x2000;
        static const uint16_t PRG_ROM_SIZE       = 0x8000;

        //Status register flags
        enum StatusFlags
        {
            FLAG_CARRY             = 0x01,
            FLAG_ZERO              = 0x02,
            FLAG_INTERRUPT_DISABLE = 0x04,
            FLAG_DECIMAL_MODE      = 0x08,
            FLAG_BREAK             = 0x10,
            FLAG_OVERFLOW          = 0x40,
            FLAG_NEGATIVE          = 0x80
        };

        //Tables
        static AddressingMode AddrModesTable[256];
        static Opcode         OpcodesTable[256];
        static uint32_t       TicksTable[256];

        //Registers
        std::uint16_t PC = 0x00; //On reset PC = *ResetHandlerAddr;
        std::uint8_t  SP = 0xFF;
        std::uint8_t  A  = 0x00;
        std::uint8_t  X  = 0x00;
        std::uint8_t  Y  = 0x00;
        std::uint8_t  P  = 0x34; //Status register

        //Bus
        NesBus* m_bus = nullptr;

        //Memory
        //std::uint8_t   Memory[0x10000];                              //$0000-$FFFF
        //std::uint8_t*  ZeroPage        = Memory;                     //$0000–$00FF
        //std::uint8_t*  Stack           = Memory + 0x0100;            //$0100–$01FF
        //std::uint8_t*  InternalRAM     = Memory + 0x0200;            //$0200–$07FF -> $0000-$07FF, mirrored at $0800-$0FFF, $1000-$17FF, $1800-$1FFF
        //std::uint8_t*  PpuRegisters    = Memory + 0x2000;            //$2000-$2007, mirrored through $2008-$3FFF every 8 bytes
        //std::uint8_t*  ApuRegisters    = Memory + 0x4000;            //$4000-$401F, except $4014,$4016,$4017
        //std::uint8_t*  DmaSpriteMem    = Memory + 0x4014;            //$4014
        //std::uint8_t*  Controller1     = Memory + 0x4016;            //$4016
        //std::uint8_t*  Controller2     = Memory + 0x4017;            //$4017
        //std::uint8_t*  ExpansionROM    = Memory + 0x4020;            //$4020–$5FFF
        //std::uint8_t*  SaveRAM         = Memory + 0x6000;            //$6000–$7FFF
        //std::uint8_t*  PrgROM          = Memory + 0x8000;            //$8000–$FFFF
        //std::uint16_t* NmiVectorAddr   = (uint16_t*)Memory + 0xFFFA; //$FFFA–$FFFB
        //std::uint16_t* ResetVectorAddr = (uint16_t*)Memory + 0xFFFC; //$FFFC–$FFFD
        //std::uint16_t* BrkVectorAddr   = (uint16_t*)Memory + 0xFFFE; //$FFFE–$FFFF


        //Accumulator mode
        //Workaround to deal with the accumulator mode.
        bool m_isAccumulatorMode = false; 

        //Ticks
        uint32_t m_ticks = 0;
        uint32_t m_tickOffset = 0;

        //Debug
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;


        //Flags related functions
        void checkNegative(uint16_t val);
        void checkZero(uint16_t val);

        //Reading
        uint16_t read16(uint16_t address);

        //Stack operations
        uint8_t  pull8();
        uint16_t pull16();
        void     push8(uint8_t value);
        void     push16(uint16_t value);
       
        //Branching
        void branch(uint16_t off_address);

        //Interrupts
        void irq();
        void nmi();
        void handleInterrupts();
        

        //Addressing modes
        uint16_t absl(); //Absolute                          : $0000		
        uint16_t absx(); //Absolute, X                       : $0000,X
        uint16_t absy(); //Absolute, Y                       : $0000,Y
        uint16_t acc();  //Accumulator
        uint16_t imm();  //Immediate                         : #$00
        uint16_t imp();  //Implied
        uint16_t ind();  //Indirect                          : ($0000)
        uint16_t indx(); //Zero Page Indexed Indirect with X : ($00, X)
        uint16_t indy(); //Zero Page Indirect Indexed with Y : ($00), Y
        uint16_t rel();  //Relative                          : PC + #$00
        uint16_t zp();   //Zero Page                         : $00
        uint16_t zpx();  //Zero Page, X                      : $00, X
        uint16_t zpy();  //Zero Page, Y                      : $00, Y


        //Opcodes

        //--Storage--
        void lda(uint16_t address); //Load A with M
        void ldx(uint16_t address); //Load X with M
        void ldy(uint16_t address); //Load Y with M
        void sta(uint16_t address); //Store A in M
        void stx(uint16_t address); //Store X in M
        void sty(uint16_t address); //Store Y in M
        void tax(uint16_t address); //Transfer A  to X
        void tay(uint16_t address); //Transfer A  to Y
        void txa(uint16_t address); //Transfer X  to A
        void tya(uint16_t address); //Transfer Y  to A
        void tsx(uint16_t address); //Transfer SP to X
        void txs(uint16_t address); //Transfer X  to SP

        //--Math--
        void adc(uint16_t address); //Add M to A with Carry
        void dec(uint16_t address); //Decrement M by 1
        void dex(uint16_t address); //Decrement X by 1
        void dey(uint16_t address); //Decrement Y by 1
        void inc(uint16_t address); //Increment M by 1
        void inx(uint16_t address); //Increment X by 1
        void iny(uint16_t address); //Increment Y by 1
        void sbc(uint16_t address); //Subtract M from A with Borrow

        //--Bitwise--
        void AND(uint16_t address); //"AND" M with A
        void asl(uint16_t address); //Shift Left 1 Bit of A
        void bit(uint16_t address); //Test Bits in M with A
        void eor(uint16_t address); //"XOR" M with A
        void lsr(uint16_t address); //Shift Right 1 Bit of A
        void ora(uint16_t address); //"OR" M with A
        void rol(uint16_t address); //Rotate One Bit Left
        void ror(uint16_t address); //Rotate One Bit Right

        //--Branch-- (precalculate address or change for relative address)
        void bcs(uint16_t address); //Branch on Carry Set
        void bcc(uint16_t address); //Branch on Carry Clear
        void beq(uint16_t address); //Branch on Result Zero
        void bne(uint16_t address); //Branch on Result not Zero
        void bmi(uint16_t address); //Branch on Result Minus
        void bpl(uint16_t address); //Branch on Result Plus
        void bvs(uint16_t address); //Branch on Overflow Set
        void bvc(uint16_t address); //Branch on Overflow Clear

        //--Jump--
        void jmp(uint16_t address); //Jump to Location
        void jsr(uint16_t address); //Jump to Location Save Return Address
        void rti(uint16_t address); //Return from Interrupt
        void rts(uint16_t address); //Return from Subroutine	

        //--Registers--
        void clc(uint16_t address); //Clear Carry Flag
        void cld(uint16_t address); //Clear Decimal Flag
        void cli(uint16_t address); //Clear Interrupt Disable Flag
        void clv(uint16_t address); //Clear Overflow Flag
        void cmp(uint16_t address); //Compare M with A
        void cpx(uint16_t address); //Compare M with X
        void cpy(uint16_t address); //Compare M with Y
        void sec(uint16_t address); //Set Carry Flag
        void sed(uint16_t address); //Set Decimal Flag
        void sei(uint16_t address); //Set Interrupt Disable Flag

        //--Stack--
        void pha(uint16_t address); //Push A on Stack
        void php(uint16_t address); //Push Processor Status (P) on Stack
        void pla(uint16_t address); //Pull A from Stack
        void plp(uint16_t address); //Pull Processor Status (P) from Stack

        //--System--
        void brk(uint16_t address); //Does nothing ? (or set interrupt flag and continue ?)
        void nop(uint16_t address); //No operation
        


    public:
        NesCpu(NesBus* bus);
        ~NesCpu();

        //Core CPU functions
        uint32_t getTicks();
        void load(std::istream& saveStream);
        void reset();
        void save(std::ostream& saveStream);
        void start();
        void stop();
        void tick();

        //Debugging
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }
    };
}