//Author: Remi Pelletier
//File:   NesAPU.h
//Desc.:  Declaration of the NesApu class used to emulate
//        the NES APU.

#pragma once
#include <cstdint>
#include "ILoggable.h"
#include "ISerializable.h"
#include "NesBus.h"

namespace nesremu
{
    class NesApu : public ILoggable, public ISerializable
    {
        NesBus* m_bus = nullptr;
        uint32_t m_ticks = 0;


    public:
        NesApu(NesBus* bus);
        ~NesApu();

        //Core APU functions.
        uint32_t getTicks();
        void reset();
        void start();
        void stop();
        void tick();

        //Saving
        virtual void load(std::istream& saveStream);
        virtual void save(std::ostream& saveStream);

    };
}