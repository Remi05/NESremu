#include "NesROM.h"


namespace nesremu
{
    NesRom::NesRom() { }

    NesRom::~NesRom() { }


    void NesRom::load(std::istream& romStream)
    {

    }

    uint8_t NesRom::read(uint16_t address)
    {
        return 0;
    }

    void NesRom::write(uint16_t address, uint8_t value)
    {

    }

}
