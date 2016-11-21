#pragma once

#include <cstdint>
#include <iostream>
#include "ILoggable.h"
#include "NesIOComponent.h"

//TO DO: Write NesROM class and add support for loading ROM from .nes file.

namespace nesremu
{

    static const int INES_HEADER_SIZE = 16;

    struct iNesHeader
    {
        uint8_t id[4];
        uint8_t prgRomSize;
        uint8_t chrRomSize;
        uint8_t flags6;
        uint8_t flags7;
        uint8_t zero[8];
    };

    struct iNesHeader2
    {
        uint8_t id[4];
        uint8_t prgRomSize;
        uint8_t chrRomSize;
        uint8_t flags6;
        uint8_t flags7;
        uint8_t mapperVariant;
        uint8_t romSizesUpperBits; //Upper 4 bits: Additionnal 4 bits for CHR ROM, Lower 4 bits: additionnal 4 bits for PRG ROM
        uint8_t prgRamSize;
        uint8_t vramSize;
        uint8_t tvSystem;
        uint8_t vsHardware;
        uint8_t zero[2];
    };


    class NesRom : public NesIoComponent, public ILoggable
    {
        uint32_t PrgRomSize = 0;
        uint32_t ChrRomSize = 0;
        uint32_t PrgRamSize = 0;
        uint32_t VRamSize   = 0;
        uint8_t* PrgRom = nullptr;
        uint8_t* ChrRom = nullptr;
        uint8_t* PrgRam = nullptr;
        uint8_t* VRam   = nullptr;

        //Debugging
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;


    public:
        NesRom();
        ~NesRom();

        void load(std::istream& romStream);
        virtual uint8_t read(uint16_t address);
        virtual void write(uint16_t address, uint8_t value);

        //Debugging
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }

    };

}