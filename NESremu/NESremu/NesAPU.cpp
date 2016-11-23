#include "NesApu.h"

namespace nesremu
{
    //Constructor and destructor
    NesApu::NesApu(NesBus* bus)
        :m_bus(bus) {}

    NesApu::~NesApu() {}


    //Core APU functions
    uint32_t NesApu::getTicks()
    {
        return m_ticks;
    }

    void NesApu::load(std::istream& saveStream)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "APU:\t Loading..." << std::endl;
        }
    }

    void NesApu::reset()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "APU:\t Resetting..." << std::endl;
        }
    }

    void NesApu::save(std::ostream& saveStream)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "APU:\t Saving..." << std::endl;
        }
    }

    void NesApu::start()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "APU:\t Starting..." << std::endl;
        }
    }

    void NesApu::stop()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "APU:\t Stopping..." << std::endl;
        }
    }

    void NesApu::tick() {}

}