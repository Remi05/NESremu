//Author: Remi Pelletier
//File:   NesPpuReg.h
//Desc.:  Declaration of the NesPpuReg class used to
//        represent the NES PPU registers.

#pragma once
#include <cstdint>
#include "ILoggable.h"
#include "NesIOComponent.h"


namespace nesremu
{
    class NesPpuReg : public NesIoComponent, public ILoggable
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

        //Debugging
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;


    public:
        NesPpuReg();
        ~NesPpuReg();

        //Core PPU registers functions
        virtual uint8_t read(uint16_t address);
        virtual void write(uint16_t address, uint8_t value);

        //Debugging
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }
    };
}
