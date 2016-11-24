#include "NesRom.h"


namespace nesremu
{
    //Constructor and destructor
    NesRom::NesRom() { }

    NesRom::~NesRom() { }


    //IO
    uint8_t NesRom::read(uint16_t address)
    {
        return 0;
    }

    void NesRom::write(uint16_t address, uint8_t value)
    {

    }


    NesRom* NesRom::load(std::istream& romStream)
    {
        return new NesRom();
    }

}
