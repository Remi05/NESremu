//Author: Remi Pelletier
//File:   NesBus.h
//Desc.:  Declaration of the NesBus class used to connect
//        the various components.

#pragma once
#include <cstdint>
#include <map>
#include <vector>
#include "ILoggable.h"
#include "NesIOComponent.h"

namespace nesremu
{
    using MappingCondition = bool(*)(uint16_t);
    using AddressFormatter = uint16_t(*)(uint16_t);

    enum LinkType { MAP_READ = 0b01, MAP_WRITE = 0b10, MAP_RW = 0b11 };

    class NesBus : public ILoggable
    {
    private:
        struct NesMemoryLink
        {
            NesIoComponent*  ioComponent;
            AddressFormatter addrFormatter;
            uint16_t start;
            uint32_t end;
            LinkType type;
        };

        std::map<uint16_t, NesMemoryLink> m_readMemoryLinks;
        std::map<uint16_t, NesMemoryLink> m_writeMemoryLinks;

        //Debugging
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;

        bool isInRange(const NesMemoryLink& link, uint16_t address);
        bool isValidRead(const NesMemoryLink& link, uint16_t address);
        bool isValidWrite(const NesMemoryLink& link, uint16_t address);

        //std::vector<NesMemoryLink> m_memoryLinks;


    public:
        void map(NesIoComponent* ioComponent, uint16_t startAddr, uint16_t rangeSize, 
                 AddressFormatter addrFormatter, LinkType type);
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

        //Debugging
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }
    };
}