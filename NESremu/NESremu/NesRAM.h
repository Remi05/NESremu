//Author: Remi Pelletier
//File:   NesRAM.h
//Desc.:  Declaration of the NesRam class used to emulate
//        a bank of RAM.


#pragma once
#include <cstdint>
#include "ILoggable.h"
#include "ISerializable.h"
#include "NesIOComponent.h"

namespace nesremu
{
    class NesRam : public NesIoComponent, public ILoggable, public ISerializable
    {
        uint32_t m_size = 0;
        uint8_t* m_memory = nullptr;


    public:
        NesRam(uint32_t size);
        ~NesRam();

        //IO
        virtual uint8_t read(uint16_t address);
        virtual void write(uint16_t address, uint8_t value);

        //Saving
        virtual void load(std::istream& saveStream);
        virtual void save(std::ostream& saveStream);
    };

}