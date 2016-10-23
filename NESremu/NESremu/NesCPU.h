#pragma once
#include <cstdint>
#include <iostream>


namespace NESremu
{

    //Misc.
    template<class T>
    T setBits(T num, T mask, bool bitVal)
    {
        return bitVal ? num | mask : num & ~mask;
    }



    class NesCpu
    {
    private:
        using AddressingMode = void(NesCpu::*)();
        using Opcode         = void(NesCpu::*)();

        //Memory constants
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

        //Memory
        std::uint8_t   Memory[0x10000];                              //$0000-$FFFF
        std::uint8_t*  ZeroPage        = Memory;                     //$0000–$00FF
        std::uint8_t*  Stack           = Memory + 0x0100;            //$0100–$01FF
        std::uint8_t*  InternalRAM     = Memory + 0x0200;            //$0200–$07FF -> $0000-$07FF, mirrored at $0800-$0FFF, $1000-$17FF, $1800-$1FFF
        std::uint8_t*  PpuRegisters    = Memory + 0x2000;            //$2000-$2007, mirrored through $2008-$3FFF every 8 bytes
        std::uint8_t*  ApuRegisters    = Memory + 0x4000;            //$4000-$401F, except $4014,$4016,$4017
        std::uint8_t*  DmaSpriteMem    = Memory + 0x4014;            //$4014
        std::uint8_t*  Controller1     = Memory + 0x4016;            //$4016
        std::uint8_t*  Controller2     = Memory + 0x4017;            //$4017
        std::uint8_t*  ExpansionROM    = Memory + 0x4020;            //$4020–$5FFF
        std::uint8_t*  SaveRAM         = Memory + 0x6000;            //$6000–$7FFF
        std::uint8_t*  PrgROM          = Memory + 0x8000;            //$8000–$FFFF
        std::uint16_t* NmiVectorAddr   = (uint16_t*)Memory + 0xFFFA; //$FFFA–$FFFB
        std::uint16_t* ResetVectorAddr = (uint16_t*)Memory + 0xFFFC; //$FFFC–$FFFD
        std::uint16_t* BrkVectorAddr   = (uint16_t*)Memory + 0xFFFE; //$FFFE–$FFFF

        //Memory pointer (used because of different addressing modes)
        uint8_t* m_srcPtr;

        //Ticks
        uint32_t m_ticks = 0;
        uint32_t m_tickOffset = 0;

        //Debug
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;


        //Flags related functions
        void checkNegative(uint16_t val);
        void checkZero(uint16_t val);

        //Stack operations
        uint8_t  pull8();
        uint16_t pull16();
        void     push8(uint8_t value);
        void     push16(uint16_t value);


        //Addressing modes
        void absl(); //Absolute				     	     : $0000		
        void absx(); //Absolute, X						 : $0000,X
        void absy(); //Absolute, Y						 : $0000,Y
        void acc();  //Accumulator
        void imm();  //Immediate						 : #$00
        void imp();  //Implied
        void ind();  //Indirect                          : ($0000)
        void indx(); //Zero Page Indexed Indirect with X : ($00, X)
        void indy(); //Zero Page Indirect Indexed with Y : ($00), Y
        void rel();  //Relative							 : PC + #$00
        void zp();   //Zero Page						 : $00
        void zpx();  //Zero Page, X						 : $00, X
        void zpy();  //Zero Page, Y						 : $00, Y


        //Opcodes

        //--Storage--
        void lda(); //Load A with M
        void ldx(); //Load X with M
        void ldy(); //Load Y with M
        void sta(); //Store A in M
        void stx(); //Store X in M
        void sty(); //Store Y in M
        void tax(); //Transfer A  to X
        void tay(); //Transfer A  to Y
        void txa(); //Transfer X  to A
        void tya(); //Transfer Y  to A
        void tsx(); //Transfer SP to X
        void txs(); //Transfer X  to SP

        //--Math--
        void adc(); //Add M to A with Carry
        void dec(); //Decrement M by 1
        void dex(); //Decrement X by 1
        void dey(); //Decrement Y by 1
        void inc(); //Increment M by 1
        void inx(); //Increment X by 1
        void iny(); //Increment Y by 1
        void sbc(); //Subtract M from A with Borrow

        //--Bitwise--
        void AND(); //"AND" M with A
        void asl(); //Shift Left 1 Bit of A
        void bit(); //Test Bits in M with A
        void eor(); //"XOR" M with A
        void lsr(); //Shift Right 1 Bit of A
        void ora(); //"OR" M with A
        void rol(); //Rotate One Bit Left
        void ror(); //Rotate One Bit Right

        //--Branch-- (precalculate address or change for relative address)
        void bcs(); //Branch on Carry Set
        void bcc(); //Branch on Carry Clear
        void beq(); //Branch on Result Zero
        void bne(); //Branch on Result not Zero
        void bmi(); //Branch on Result Minus
        void bpl(); //Branch on Result Plus
        void bvs(); //Branch on Overflow Set
        void bvc(); //Branch on Overflow Clear

        //--Jump--
        void jmp(); //Jump to Location
        void jsr(); //Jump to Location Save Return Address
        void rti(); //Return from Interrupt
        void rts(); //Return from Subroutine	

        //--Registers--
        void clc(); //Clear Carry Flag
        void cld(); //Clear Decimal Flag
        void cli(); //Clear Interrupt Disable Flag
        void clv(); //Clear Overflow Flag
        void cmp(); //Compare M with A
        void cpx(); //Compare M with X
        void cpy(); //Compare M with Y
        void sec(); //Set Carry Flag
        void sed(); //Set Decimal Flag
        void sei(); //Set Interrupt Disable Flag

        //--Stack--
        void pha(); //Push A on Stack
        void php(); //Push Processor Status (P) on Stack
        void pla(); //Pull A from Stack
        void plp(); //Pull Processor Status (P) from Stack

        //--System--
        void brk(); //Does nothing ? (or set interrupt flag and continue ?)
        void nop(); //No operation
        


    public:
        //Core CPU functions
        void init();
        void reset();
        void shutdown();
        void tick();

        //Debugging
        void enableLog();
        void disableLog();
        void printLog();
        void setLogStream(std::ostream& logStream);
    };
}