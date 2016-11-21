#include <algorithm>
#include <iomanip>
#include "NesBus.h"


namespace nesremu
{

    //void NesBus::map(NesIoComponent* ioComponent, MappingCondition cond, AddressFormatter addrFormatter)
    //{
    //    NesMemoryLink link = { ioComponent, cond, addrFormatter };
    //    m_memoryLinks.push_back(link);
    //}
    //
    //uint8_t NesBus::read(uint16_t address)
    //{
    //    for (auto const& link : m_memoryLinks) {
    //        if (link.cond(address)) {
    //            return link.ioComponent->read(link.addrFormatter(address));
    //        }
    //    }
    //    return 0; //Handle no link found.
    //}
    //
    //void NesBus::write(uint16_t address, uint8_t value)
    //{
    //    for (auto const& link : m_memoryLinks) {
    //        if (link.cond(address)) {
    //            link.ioComponent->write(link.addrFormatter(address), value);
    //            break;
    //        }
    //    }
    //}


    //Query validation functions.
    bool NesBus::isInRange(const NesMemoryLink& link, uint16_t address)
    {
        return address >= link.start && address < link.end;
    }

    bool NesBus::isValidRead(const NesMemoryLink& link, uint16_t address)
    {
        return isInRange(link, address) && (link.type & LinkType::MAP_READ);
    }

    bool NesBus::isValidWrite(const NesMemoryLink& link, uint16_t address)
    {
        return isInRange(link, address) && (link.type & LinkType::MAP_WRITE);
    }


    //Core bus functions.
    void NesBus::map(NesIoComponent* ioComponent, uint16_t startAddr, uint16_t rangeSize,
                     AddressFormatter addrFormatter, LinkType type)
    {
        NesMemoryLink link = { ioComponent, addrFormatter, startAddr, startAddr + rangeSize, type };
        
        if (type & LinkType::MAP_READ) {
            m_readMemoryLinks[startAddr] = link;
        }
        if (type & LinkType::MAP_WRITE) {
            m_writeMemoryLinks[startAddr] = link;
        }     
    }


    uint8_t NesBus::read(uint16_t address)
    {
        //Map the address to the corresponding component.
        auto pos = m_readMemoryLinks.upper_bound(address);
        if (pos != m_readMemoryLinks.begin()) {
            --pos;      
        }

        //Check if read is valid.
        NesMemoryLink link = pos->second;
        if (!isValidRead(link, address)) {
            //Handle invalid read.
            *m_logStream << "Bus:\t Invalid read at address $" << std::hex 
                         << std::setfill('0') << std::setw(4) << address
                         << " (start: $" << std::setfill('0') << std::setw(4) 
                         << link.start << "  end: $" << std::setfill('0') 
                         << std::setw(4) << link.end << "  valid mode: " 
                         << std::boolalpha << bool(link.type & LinkType::MAP_READ) 
                         << ")." << std::endl;
            return -1;
        }

        //Debugging
        if (m_logEnabled) {
            *m_logStream << "Bus:\t Reading at address $" 
                         << std::hex << std::setfill('0')
                         << std::setw(4) << address << "." 
                         << std::endl;
        }

        //Read and return the value.
        return link.ioComponent->read(link.addrFormatter(address));
    }


    void NesBus::write(uint16_t address, uint8_t value)
    {
        //Map the address to the corresponding component.
        auto pos = m_writeMemoryLinks.upper_bound(address);
        if (pos != m_writeMemoryLinks.begin()) {
            --pos;
        }

        //Check if the write is valid.
        NesMemoryLink link = pos->second;
        if (!isValidWrite(link, address)) {
            //Handle invalid write.
            *m_logStream << "Bus:\t Invalid write at address $" << std::hex 
                         << std::setfill('0') << std::setw(4) << address
                         << " (start: $" << std::setfill('0') << std::setw(4)
                         << link.start << "  end: $" << std::setfill('0')
                         << std::setw(4) << link.end << "  valid mode: "
                         << std::boolalpha << bool(link.type & LinkType::MAP_WRITE)
                         << ")." << std::endl;
            return;
        }

        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "Bus:\t Writing 0x" << std::hex 
                         << std::setfill('0') << std::setw(2)
                         << (int)value << " at address $" 
                         << std::setfill('0') << std::setw(4)
                         << address << "." << std::endl;
        }

        //Write the value.
        link.ioComponent->write(link.addrFormatter(address), value);
    }


}