#pragma once
#include <cstdint>
#include <iostream>
#include "ILoggable.h"
#include "NesIOComponent.h"

namespace nesremu
{
    class NesRam : public NesIoComponent, public ILoggable
    {
        uint32_t m_size = 0;
        uint8_t* m_memory = nullptr;

        //Debugging
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;


    public:
        NesRam(uint32_t size);
        ~NesRam();

        //Saving
        void load(std::istream& saveStream);
        void save(std::ostream& saveStream);

        //Core RAM functions
        virtual uint8_t read(uint16_t address);
        virtual void write(uint16_t address, uint8_t value);

        //Debugging
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }
    };

}