#pragma once
#include <iostream>

namespace nesremu
{
    class ILoggable
    {
    public:
        virtual void enableLog()  = 0;
        virtual void disableLog() = 0;
        virtual void setLogStream(std::ostream& logStream) = 0;
    };
}