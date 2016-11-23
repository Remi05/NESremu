//Author: Remi Pelletier
//File:   NesController.h
//Desc.:  Declaration of the NesController class used to 
//        emulate a NES joypad.

#pragma once
#include <cstdint>
#include "ILoggable.h"
#include "NesIOComponent.h"

namespace nesremu
{
    class NesController : public NesIoComponent, public ILoggable
    {
    private:
        enum NesButtons
        {
            BUTTON_A = 0x01,
            BUTTON_B = 0x02,
            BUTTON_SELECT = 0x04,
            BUTTON_START = 0x08,
            BUTTON_UP = 0x10,
            BUTTON_DOWN = 0x20,
            BUTTON_LEFT = 0x40,
            BUTTON_RIGHT = 0x80
        };

        //Debugging
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;


    public:        
        virtual uint8_t read(uint16_t address);
        virtual void write(uint16_t address, uint8_t value);

        //Debugging
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }

    };
}
