#include <iomanip>
#include "NesPpuReg.h"

namespace nesremu
{
    //Constructor and destructor
    NesPpuReg::NesPpuReg() {}

    NesPpuReg::~NesPpuReg() {}


    //IO
    uint8_t NesPpuReg::read(uint16_t address)
    {
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
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Reading at address $2002 (PPUSTATUS)." << std::endl;
            }
            value = m_ppustatus;
            break;
        case OAMADDR:
            //Handle invalid read of the OAMADDR register.
            *m_logStream << "PPU Reg:\t Invalid read at address $2003 (OAMADDR)." << std::endl;
            break;
        case OAMDATA:
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Reading at address $2004 (OAMDATA)." << std::endl;
            }
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
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Reading at address $2007 (PPUDATA)." << std::endl;
            }
            //Read from VRAM
            //value = read(m_ppuaddr);
            m_ppuaddr += 1 << ((m_ppuctrl & FLAG_VRAM_INC) | ((m_ppuctrl & FLAG_VRAM_INC) >> 2)); //1 if FLAG_VRAM_INC is set else 32
            break;
        default:
            //Handle invalid read.
            *m_logStream << "PPU Reg:\t Invalid read at address $" 
                         << std::setfill('0') << std::setw(4) 
                         << address << "." << std::endl;
            break;
        }

        return value;
    }

    void NesPpuReg::write(uint16_t address, uint8_t value)
    {
        switch (address) {
        case PPUCTRL:
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Writing 0x" << std::setfill('0')
                             << std::setw(2) << value 
                             << "at address $2000 (PPUCTRL)." << std::endl;
            }
            m_ppuctrl = value;
            break;
        case PPUMASK:
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Writing 0x" << std::setfill('0')
                             << std::setw(2) << value
                             << "at address $2000 (PPUMASK)." << std::endl;
            }
            m_ppumask = value;
            break;
        case PPUSTATUS:
            //Handle invalid write on the PPUSTATUS register.
            *m_logStream << "PPU Reg:\t Invalid write at address $2002 (PPUSTATUS)." << std::endl;
            break;
        case OAMADDR:
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Writing 0x" << std::setfill('0')
                    << std::setw(2) << value
                    << "at address $2003 (OAMADDR)." << std::endl;
            }
            //Write OAM address.
            m_oamaddr = value; //?
            break;
        case OAMDATA:
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Writing 0x" << std::setfill('0')
                << std::setw(2) << value
                << "at address $2004 (OAMDATA)." << std::endl;
            }
            //Write to OAM
            //Increment OAM address.
            ++m_oamaddr;
            break;
        case PPUSCROLL:
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Writing 0x" << std::setfill('0')
                             << std::setw(2) << value
                             << "at address $2005 (PPUSCROLL)." << std::endl;
            }
            //Handle write to PPUSCROLL
            break;
        case PPUADDR:
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Writing 0x" << std::setfill('0')
                             << std::setw(2) << value
                             << "at address $2006 (PPUADDR)." << std::endl;
            }
            m_ppuaddr = (m_ppuaddr << 8) | value;
            break;
        case PPUDATA:
            //Debugging
            if (m_logEnabled) {
                *m_logStream << "PPU Reg:\t Writing 0x" << std::setfill('0')
                             << std::setw(2) << value
                             << "at address $2007 (PPUDATA)." << std::endl;
            }
            //Write to VRAM
            m_ppuaddr += 1 << ((m_ppuctrl & FLAG_VRAM_INC) | ((m_ppuctrl & FLAG_VRAM_INC) >> 2)); //1 if FLAG_VRAM_INC is set else 32
            break;
        default:
            //Handle invalid write.
            *m_logStream << "PPU Reg:\t Invalid write at address $"
                         << std::setfill('0') << std::setw(4) 
                         << address << "." << std::endl;
        }
    }


    //Saving
    void NesPpuReg::load(std::istream& saveStream)
    {
        //Debugging
        if (m_logEnabled) {
            *m_logStream << "PPU Reg:\t Loading..." << std::endl;
        }

        //Load PPU registers from save stream.
        saveStream.read((char*)&m_ppuctrl,   sizeof(m_ppuctrl));
        saveStream.read((char*)&m_ppumask,   sizeof(m_ppumask));
        saveStream.read((char*)&m_ppustatus, sizeof(m_ppustatus));
        saveStream.read((char*)&m_oamaddr,   sizeof(m_oamaddr));
        saveStream.read((char*)&m_ppuscroll, sizeof(m_ppuscroll));
        saveStream.read((char*)&m_ppuaddr,   sizeof(m_ppuaddr));
    }

    void NesPpuReg::save(std::ostream& saveStream)
    {
        //Debugging
        if (m_logEnabled) {
            *m_logStream << "PPU Reg:\t Saving..." << std::endl;
        }

        //Save PPU registers to save stream.
        saveStream.write((char*)&m_ppuctrl,   sizeof(m_ppuctrl));
        saveStream.write((char*)&m_ppumask,   sizeof(m_ppumask));
        saveStream.write((char*)&m_ppustatus, sizeof(m_ppustatus));
        saveStream.write((char*)&m_oamaddr,   sizeof(m_oamaddr));
        saveStream.write((char*)&m_ppuscroll, sizeof(m_ppuscroll));
        saveStream.write((char*)&m_ppuaddr,   sizeof(m_ppuaddr));
    }
}