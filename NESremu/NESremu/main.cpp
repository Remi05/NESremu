#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "NesEmu.h"

int main()
{
    nesremu::NesEmu emulator;

    emulator.enableLog();
    emulator.start(std::cin);

    emulator.m_bus->write(0x0000, 247);
    std::cout << std::hex << (int)emulator.m_bus->read(0x0000) << std::endl;
    std::cout << std::hex << (int)emulator.m_bus->read(0x0800) << std::endl;

    emulator.m_bus->write(0x0900, 37);
    std::cout << std::hex << (int)emulator.m_bus->read(0x0900) << std::endl;
    std::cout << std::hex << (int)emulator.m_bus->read(0x0100) << std::endl;

    std::cout << std::hex << (int)emulator.m_bus->read(0x4016) << std::endl;
    std::cout << std::hex << (int)emulator.m_bus->read(0x4017) << std::endl;

    std::cout << std::hex << (int)emulator.m_bus->read(0x2000) << std::endl;

    emulator.stop();

    std::cin.get();

    return 0;
}