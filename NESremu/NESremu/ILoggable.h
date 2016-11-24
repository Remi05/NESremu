//Author: Remi Pelletier
//File:   ILoggable.h
//Desc.:  Declaration of the ILoggable interface.

#pragma once
#include <iostream>

namespace nesremu
{
    class ILoggable
    {
    protected:
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;

    public:
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }
    };
}