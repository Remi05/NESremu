//Author: Remi Pelletier
//File:   NesIOComponent.h
//Desc.:  Declaration of the NesIOComponent interface.


#pragma once
#include <cstdint>

namespace nesremu
{
    class NesIoComponent
    {
    public:
        virtual uint8_t read(uint16_t address) = 0;
        virtual void write(uint16_t address, uint8_t value) = 0;
    };
}