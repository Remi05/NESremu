//Author: Remi Pelletier
//File:   NesPpuReg.h
//Desc.:  Declaration of the NesPpuReg class used to
//        represent the NES PPU registers.

#pragma once
#include <cstdint>
#include "ILoggable.h"
#include "ISerializable.h"
#include "NesIOComponent.h"


namespace nesremu
{
    class NesPpuReg : public NesIoComponent, public ILoggable, public ISerializable
    {
    private:
        enum PpuRegisters {  PPUCTRL   = 0x2000,
                             PPUMASK   = 0x2001,
                             PPUSTATUS = 0x2002,
                             OAMADDR   = 0x2003,
                             OAMDATA   = 0x2004,
                             PPUSCROLL = 0x2005,
                             PPUADDR   = 0x2006,
                             PPUDATA   = 0x2007 };

        enum PpuCtrlFlags { FLAG_NAME_TBL     = 0b00000011,
                            FLAG_VRAM_INC     = 0b00000100,
                            FLAG_SPR_PTRN_TBL = 0b00001000,
                            FLAG_BCK_PTRN_TBL = 0b00010000,
                            FLAG_SPRITE_SIZE  = 0b00100000,
                            FLAG_MASTER_SLAVE = 0b01000000,
                            FLAG_VBLANK_NMI   = 0b10000000 };
        
        uint8_t  m_ppuctrl   = 0;
        uint8_t  m_ppumask   = 0;
        uint8_t  m_ppustatus = 0;
        uint8_t  m_oamaddr   = 0;
        uint8_t  m_ppuscroll = 0;
        uint16_t m_ppuaddr   = 0;


    public:
        NesPpuReg();
        ~NesPpuReg();

        //IO
        virtual uint8_t read(uint16_t address);
        virtual void write(uint16_t address, uint8_t value);

        //Saving
        virtual void load(std::istream& saveStream);
        virtual void save(std::ostream& saveStream);

    };
}
