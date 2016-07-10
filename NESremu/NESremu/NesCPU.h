#pragma once
#include <cstdint>
#include <iostream>

//Use classes instead of namespaces?

namespace NesCPU
{
	//Registers
	std::uint16_t PC; //On reset PC = *ResetHandlerAddr;
	std::uint8_t  SP = 0xFF;
	std::uint8_t  A  = 0x00;
	std::uint8_t  X  = 0x00;
	std::uint8_t  Y  = 0x00;
	std::uint8_t  P  = 0x34; //Status register
	
	//Memory
	std::uint8_t   Memory[0x10000];                               //$0000-$FFFF
	std::uint8_t*  ZeroPage         = Memory;                     //$0000–$00FF
	std::uint8_t*  Stack            = Memory + 0x0100;            //$0100–$01FF
	std::uint8_t*  InternalRAM      = Memory + 0x0200;            //$0200–$07FF -> $0000-$07FF, mirrored at $0800-$0FFF, $1000-$17FF, $1800-$1FFF
	std::uint8_t*  PpuRegisters     = Memory + 0x2000;            //$2000-$2007, mirrored through $2008-$3FFF every 8 bytes
	std::uint8_t*  ApuRegisters     = Memory + 0x4000;            //$4000-$401F, except $4014,$4016,$4017
	std::uint8_t*  DmaSpriteMem     = Memory + 0x4014;            //$4014
	std::uint8_t*  Controller1      = Memory + 0x4016;            //$4016
	std::uint8_t*  Controller2      = Memory + 0x4017;            //$4017
	std::uint8_t*  ExpansionROM     = Memory + 0x4020;            //$4020–$5FFF
	std::uint8_t*  SaveRAM          = Memory + 0x6000;            //$6000–$7FFF
	std::uint8_t*  PrgROM           = Memory + 0x8000;            //$8000–$FFFF
	std::uint16_t* NmiVectorAddr    = (uint16_t*)Memory + 0xFFFA; //$FFFA–$FFFB
	std::uint16_t* ResetVectorAddr  = (uint16_t*)Memory + 0xFFFC; //$FFFC–$FFFD
	std::uint16_t* BrkVectorAddr    = (uint16_t*)Memory + 0xFFFE; //$FFFE–$FFFF

	//Status register pointers
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
	extern void (*AddrModesTable[256])();
	extern void (*OpcodesTable[256])();
	extern uint32_t TicksTable[256];

	//Memory pointer (used because of different addressing modes)
	uint8_t* g_srcPtr;


	//Ticks
	uint32_t g_ticks      = 0;
	uint32_t g_tickOffset = 0;


	//Core CPU functions
	void run();


	//Flags related functions
	void checkNegative(uint16_t val);
	void checkZero(uint16_t val);


	//Misc.
	template<class T>
	T setBits(T num, T mask, bool bitVal)
	{
		return bitVal ? num | mask : num & ~mask;
	}


	//Stack operations
	uint8_t  pull8();
	uint16_t pull16();
	void     push8(uint8_t value);
	void     push16(uint16_t value);


	//Addressing modes
	//Change name of abs() to prevent conflict?
	void abs();  //Absolute							 : $0000		
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
	void LDA(); //Load A with M
	void LDX(); //Load X with M
	void LDY(); //Load Y with M
	void STA(); //Store A in M
	void STX(); //Store X in M
	void STY(); //Store Y in M
	void TAX(); //Transfer A  to X
	void TAY(); //Transfer A  to Y
	void TXA(); //Transfer X  to A
	void TYA(); //Transfer Y  to A
	void TSX(); //Transfer SP to X
	void TXS(); //Transfer X  to SP

	//--Math--
	void ADC(); //Add M to A with Carry
	void DEC(); //Decrement M by 1
	void DEX(); //Decrement X by 1
	void DEY(); //Decrement Y by 1
	void INC(); //Increment M by 1
	void INX(); //Increment X by 1
	void INY(); //Increment Y by 1
	void SBC(); //Subtract M from A with Borrow

	//--Bitwise--
	void AND(); //"AND" M with A
	void ASL(); //Shift Left 1 Bit of A
	void BIT(); //Test Bits in M with A
	void EOR(); //"XOR" M with A
	void LSR(); //Shift Right 1 Bit of A
	void ORA(); //"OR" M with A
	void ROL(); //Rotate One Bit Left
	void ROR(); //Rotate One Bit Right

	//--Branch-- (precalculate address or change for relative address)
	void BCS(); //Branch on Carry Set
	void BCC(); //Branch on Carry Clear
	void BEQ(); //Branch on Result Zero
	void BNE(); //Branch on Result not Zero
	void BMI(); //Branch on Result Minus
	void BPL(); //Branch on Result Plus
	void BVS(); //Branch on Overflow Set
	void BVC(); //Branch on Overflow Clear

	//--Jump--
	void JMP(); //Jump to Location
	void JSR(); //Jump to Location Save Return Address
	void RTI(); //Return from Interrupt
	void RTS(); //Return from Subroutine	

	//--Registers--
	void CLC(); //Clear Carry Flag
	void CLD(); //Clear Decimal Flag
	void CLI(); //Clear Interrupt Disable Flag
	void CLV(); //Clear Overflow Flag
	void CMP(); //Compare M with A
	void CPX(); //Compare M with X
	void CPY(); //Compare M with Y
	void SEC(); //Set Carry Flag
	void SED(); //Set Decimal Flag
	void SEI(); //Set Interrupt Disable Flag

	//--Stack--
	void PHA(); //Push A on Stack
	void PHP(); //Push Processor Status (P) on Stack
	void PLA(); //Pull A from Stack
	void PLP(); //Pull Processor Status (P) from Stack

	//--System--
	void BRK(); //Does nothing ? (or set interrupt flag and continue ?)
	void NOP(); //No operation




	//Debugging
	bool g_cpuLogEnabled = false;
	std::ostream* g_cpuLogStream = &std::clog;

	void enableCpuLog();
	void disableCpuLog();
	void setCpuLogStream(std::ostream& logStream);
	void printCpuLog();

}
