#include "NesController.h"

namespace nesremu 
{
    //IO
    uint8_t NesController::read(uint16_t address)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "Joy:\t Reading." << std::endl;
        }
        return 0;
    }

    void NesController::write(uint16_t address, uint8_t value)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "Joy:\t Writing " << (int)value << "." << std::endl;
        }
    }

}