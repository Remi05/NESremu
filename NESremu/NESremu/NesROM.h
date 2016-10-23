#pragma once

#include <cstdint>
#include <string>

//TO DO: Write NesROM class and add support for loading ROM from .nes file.

static const int INES_HEADER_SIZE = 16;

struct iNesHeader
{
    uint8_t id[4];
    uint8_t prgRomSize;
    uint8_t chrRomSize;
    uint8_t flags6;
    uint8_t flags7;
    uint8_t zero[8];
};

struct iNesHeader2
{
    uint8_t id[4];
    uint8_t prgRomSize;
    uint8_t chrRomSize;
    uint8_t flags6;
    uint8_t flags7;
    uint8_t mapperVariant;
    uint8_t romSizesUpperBits; //Upper 4 bits: Additionnal 4 bits for CHR ROM, Lower 4 bits: additionnal 4 bits for PRG ROM
    uint8_t prgRamSize;
    uint8_t vramSize;
    uint8_t tvSystem;
    uint8_t vsHardware;
    uint8_t zero[2];
};


class NesROM
{
public:

    uint32_t PrgRomSize = 0;
    uint32_t ChrRomSize = 0;
    uint32_t PrgRamSize = 0;
    uint32_t VRamSize   = 0;
    uint8_t* PrgRom = nullptr;
    uint8_t* ChrRom = nullptr;
    uint8_t* PrgRam = nullptr;
    uint8_t* VRam   = nullptr;

    NesROM();
    NesROM(const std::string& fileName);
    ~NesROM();

};