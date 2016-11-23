//Author: Remi Pelletier
//File:   NesAPU.h
//Desc.:  Declaration of the NesApu class used to emulate
//        the NES APU.

#pragma once
#include <cstdint>
#include "ILoggable.h"
#include "NesBus.h"

namespace nesremu
{
    class NesApu : public ILoggable
    {
        NesBus* m_bus = nullptr;
        uint32_t m_ticks = 0;

        //Debugging
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;


    public:
        NesApu(NesBus* bus);
        ~NesApu();

        //Core APU functions.
        uint32_t getTicks();
        void load(std::istream& saveStream);
        void reset();
        void save(std::ostream& saveStream);
        void start();
        void stop();
        void tick();

        //Debugging
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }

    };
}