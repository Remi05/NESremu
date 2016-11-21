#pragma once
#include <cstdint>
#include <iostream>
#include "NesAPU.h"
#include "NesBus.h"
#include "NesController.h"
#include "NesCPU.h"
#include "NesPPU.h"
#include "NesRAM.h"
#include "NesROM.h"

//TO DO: Write emulator logic using the various components.

namespace nesremu
{

    enum LogFlags { LOG_APU  = 0x0001,
                    LOG_BUS  = 0x0002,
                    LOG_CPU  = 0x0004,
                    LOG_PPU  = 0x0008,
                    LOG_RAM  = 0x0010,
                    LOG_ROM  = 0x0020,
                    LOG_VRAM = 0x0040,
                    LOG_JOY1 = 0x0080,
                    LOG_JOY2 = 0x0100,
                    LOG_ALL  = 0x01FF,
                    LOG_NONE = 0x0000 };

    enum NesEmuState { PLAYING, PAUSED, STOPPED };


    class NesEmu
    {
    public:
        static const uint16_t CPU_RAM_ADDR     = 0x0000;
        static const uint32_t CPU_RAM_SIZE     = 0x2000;
        static const uint16_t CPU_RAM_MASK     = 0x07FF;
        static const uint16_t ROM_ADDR         = 0x8000;
        static const uint16_t ROM_SIZE         = 0x8000;
        static const uint32_t PPU_VRAM_SIZE    = 0x0800;
        static const uint16_t CONTROLLER1_ADDR = 0x4016;
        static const uint16_t CONTROLLER2_ADDR = 0x4017;

        AddressFormatter NONE_ADDRESS_FORMATTER = [](uint16_t addr) -> uint16_t { return addr; };

        //MappingCondition CPU_RAM_MAPPING_CONDITION = [](uint16_t addr) -> bool     { return addr < CPU_RAM_SIZE; };
        AddressFormatter CPU_RAM_ADDRESS_FORMATTER = [](uint16_t addr) -> uint16_t { return addr & CPU_RAM_MASK; };

        //MappingCondition CONTROLLER1_MAPPING_CONDITION = [](uint16_t addr) -> bool { return addr == CONTROLLER1_ADDR; };
        //MappingCondition CONTROLLER2_MAPPING_CONDITION = [](uint16_t addr) -> bool { return addr == CONTROLLER2_ADDR; };

        //MappingCondition ROM_MAPPING_CONDITION = [](uint16_t addr) -> bool     { return addr >= ROM_ADDR; };
        AddressFormatter ROM_ADDRESS_FORMATTER = [](uint16_t addr) -> uint16_t { return addr - ROM_ADDR; };


        NesApu* m_apu  = nullptr;
        NesBus* m_bus  = nullptr;
        NesCpu* m_cpu  = nullptr;
        NesPpu* m_ppu  = nullptr;
        NesRam* m_ram  = nullptr;
        NesRom* m_rom  = nullptr;
        NesRam* m_vram = nullptr;
        NesController* m_controller1 = nullptr;
        NesController* m_controller2 = nullptr;

        NesEmuState m_state = NesEmuState::STOPPED;

        //Debugging
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;
        LogFlags m_logFlags = LogFlags::LOG_NONE;


    public:
        NesEmu();
        ~NesEmu();

        //Core emulator functions
        void load(std::istream& saveStream);
        void reset();
        void run();
        void save(std::ostream& saveStream);
        void start(std::istream& romStream);
        void stop();

        //Debugging
        virtual void enableLog(uint16_t flags = LogFlags::LOG_ALL);
        virtual void disableLog(uint16_t flags = LogFlags::LOG_ALL);
        virtual void setLogStream(std::ostream& logStream);
                
    };
}