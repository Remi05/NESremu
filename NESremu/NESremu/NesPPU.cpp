#include "NesPPU.h"

namespace nesremu
{
    //Constructor and destructor
    NesPpu::NesPpu(NesBus* bus)
        :m_bus(bus) {}

    NesPpu::~NesPpu() {}


    //Core PPU functions
    uint32_t NesPpu::getTicks()
    {
        return m_ticks;
    }

    void NesPpu::load(std::istream& saveStream)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "PPU: Loading..." << std::endl;
        }
    }

    void NesPpu::reset()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "PPU:\t Resetting..." << std::endl;
        }
    }

    void NesPpu::save(std::ostream& saveStream)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "PPU: Saving..." << std::endl;
        }
    }

    void NesPpu::start()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "PPU:\t Starting..." << std::endl;
        }
    }

    void NesPpu::stop()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "PPU:\t Stopping..." << std::endl;
        }
    }

    void NesPpu::tick() {}

}