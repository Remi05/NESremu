#pragma once
#include <iostream>

namespace nesremu
{
    class ISerializable
    {
    public:
        virtual void load(std::istream& saveStream) = 0;
        virtual void save(std::ostream& saveStream) = 0;
    };
}