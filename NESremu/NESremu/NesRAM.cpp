#include <iomanip>
#include "NesRam.h"

namespace nesremu
{
    //Constructor and destructor
    NesRam::NesRam(uint32_t size)
        :m_size(size)
    {
        m_memory = new uint8_t[m_size];
    }

    NesRam::~NesRam()
    {
        delete[] m_memory;
    }


    //Core RAM functions.
    uint8_t NesRam::read(uint16_t address)
    {
        //Check if read is valid.
        if (address >= m_size) {
            //Handle index out of range.
            *m_logStream << "RAM:\t Invalid read at address $" << std::hex 
                         << std::setfill('0') << std::setw(4) << address 
                         << std::dec << " (size: " << m_size << ")." << std::endl;
            return -1;
        }

        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "RAM:\t Reading at address $" 
                         << std::setfill('0') << std::setw(4)
                         << std::hex << address << "." << std::endl;
        }

        //Read and return the value;
        return m_memory[address];
    }

    void NesRam::write(uint16_t address, uint8_t value)
    {
        //Check if write is valid.
        if (address >= m_size) {
            //Handle index out of range.
            *m_logStream << "RAM:\t Invalid write at address $" << std::hex
                         << std::setfill('0') << std::setw(4)
                         << address << std::dec << " (size: " << m_size
                         << ")." << std::endl;
            return;
        }

        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "RAM:\t Writing 0x" << std::hex << (int)value 
                         << " at address $" << std::setfill('0') 
                         << std::setw(4) << address << "." << std::endl;
        }

        //Write the given value.
        m_memory[address] = value;
    }


    //Saving
    void NesRam::load(std::istream& saveStream)
    {
        //Read the length of the data from the save stream.
        saveStream.read((char*)&m_size, sizeof(m_size));
        //Read the data from the save stream.
        saveStream.read((char*)m_memory, m_size);
    }

    void NesRam::save(std::ostream& saveStream)
    {
        //Write the length of the data to the save stream.
        saveStream.write((char*)&m_size, sizeof(m_size));
        //Write the data to the save stream.
        saveStream.write((char*)m_memory, m_size);
    }

}