#include <iomanip>
#include "NesPpuReg.h"

namespace nesremu
{
    //Constructor and destructor
    NesPpuReg::NesPpuReg() {}

    NesPpuReg::~NesPpuReg() {}


    //Core PPU registers functions
    uint8_t NesPpuReg::read(uint16_t address)
    {
        //Debugging
        if (m_logEnabled) {
            *m_logStream << "PPU Reg:\t Reading at address $" 
                         << std::setfill('0') << std::setw(4) 
                         << address << "." << std::endl;
        }

        uint8_t value = -1;

        switch (address) {
        case PPUCTRL:
            //Handle invalid read of the PPUCTRL register.
            *m_logStream << "PPU Reg:\t Invalid read at address $2000 (PPUCTRL)." << std::endl;
            break;
        case PPUMASK:
            //Handle invalid read of the PPUMASK register.
            *m_logStream << "PPU Reg:\t Invalid read at address $2001 (PPUMASK)." << std::endl;
            break;
        case PPUSTATUS:
            value = m_ppustatus;
            break;
        case OAMADDR:
            //Handle invalid read of the OAMADDR register.
            *m_logStream << "PPU Reg:\t Invalid read at address $2003 (OAMADDR)." << std::endl;
            break;
        case OAMDATA:
            //Read from OAM
            //value = read(m_oamaddr);
            break;
        case PPUSCROLL:
            //Handle invalid read of the PPUSCROLL register.
            *m_logStream << "PPU Reg:\t Invalid read at address $2005 (PPUSCROLL)." << std::endl;
            break;
        case PPUADDR:
            //Handle invalid read of the PPUADDR register.
            *m_logStream << "PPU Reg:\t Invalid read at address $2006 (PPURADDR)." << std::endl;
            break;
        case PPUDATA:
            //Read from VRAM
            //value = read(m_ppuaddr);
            m_ppuaddr += 1 << ((m_ppuctrl & FLAG_VRAM_INC) | ((m_ppuctrl & FLAG_VRAM_INC) >> 2)); //1 if FLAG_VRAM_INC is set else 32
            break;
        }

        return value;
    }


    void NesPpuReg::write(uint16_t address, uint8_t value)
    {
        //Debugging
        if (m_logEnabled) {
            *m_logStream << "PPU Reg:\t Writing 0x" << std::setfill('0') 
                         << std::setw(2) << value << " at address $" 
                         << std::setfill('0') << std::setw(4) << address 
                         << "." << std::endl;
        }

        switch (address) {
        case PPUCTRL:
            m_ppuctrl = value;
            break;
        case PPUMASK:
            m_ppumask = value;
            break;
        case PPUSTATUS:
            //Handle invalid write on the PPUSTATUS register.
            *m_logStream << "PPU Reg:\t Invalid write at address $2002 (PPUSTATUS)." << std::endl;
            break;
        case OAMADDR:
            //Write OAM address.
            m_oamaddr = value; //?
            break;
        case OAMDATA:
            //Write to OAM
            //Increment OAM address.
            ++m_oamaddr;
            break;
        case PPUSCROLL:
            //Handle write to PPUSCROLL
            break;
        case PPUADDR:
            m_ppuaddr = (m_ppuaddr << 8) | value;
            break;
        case PPUDATA:
            //Write to VRAM
            m_ppuaddr += 1 << ((m_ppuctrl & FLAG_VRAM_INC) | ((m_ppuctrl & FLAG_VRAM_INC) >> 2)); //1 if FLAG_VRAM_INC is set else 32
            break;
        }

    }

}