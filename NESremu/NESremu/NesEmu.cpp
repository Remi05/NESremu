//Author: Remi Pelletier
//File:   NesEmu.cpp
//Desc.:  Definition of the NesEmu methods.

#include "NesEmu.h"

namespace nesremu
{
    //Constructor and destructor
    NesEmu::NesEmu() {}

    NesEmu::~NesEmu()
    {
        //delete m_apu;
        //delete m_cpu;
        //delete m_ppu;
        //delete m_ram;
        //delete m_rom;
        //delete m_vram;
        //delete m_apuBus;
        //delete m_cpuBus;
        //delete m_ppuBus;
        //delete m_controller1;
        //delete m_controller2;
    }


    //Core emulator functions
    void NesEmu::reset()
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "Emu:\t Resetting..." << std::endl;
        }

        if (m_state != NesEmuState::STOPPED) {
            //m_apu->reset();
            //m_cpu->reset();
            //m_ppu->reset();
        }  
    }

    void NesEmu::run()
    {     
        if (m_state != NesEmuState::STOPPED) {
            //m_apu->tick();
            //m_cpu->tick();
            //m_ppu->tick();
        }
    }

    void NesEmu::start(std::istream& romStream)
    {
        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "Emu:\t Starting..." << std::endl;
        }

        //m_rom = NesRom::load(romStream);
        m_ram  = new NesRam(CPU_RAM_SIZE);
        //m_vram = new NesRam(PPU_VRAM_SIZE);
        m_controller1 = new NesController();
        m_controller2 = new NesController();

        m_cpuBus = new NesBus();
        //m_cpuBus->map(m_rom, ROM_ADDR, ROM_SIZE, ROM_ADDR_FORMATTER, MAP_READ);
        m_cpuBus->map(m_ram, CPU_RAM_ADDR, CPU_RAM_SIZE, CPU_RAM_ADDR_FORMATTER, MAP_RW);
        m_cpuBus->map(m_controller1, CONTROLLER1_ADDR, 1, NONE_ADDR_FORMATTER, MAP_RW);
        m_cpuBus->map(m_controller2, CONTROLLER2_ADDR, 1, NONE_ADDR_FORMATTER, MAP_READ); //Writes to 0x4017 go to the APU.
        
        //m_ppuBus = new NesBus();
        //m_ppuBus->map(m_vram, PPU_VRAM_ADDR, PPU_VRAM_SIZE, PPU_VRAM_ADDR_FORMATTER, MAP_RW);

        //m_apu = new NesApu(m_apuBus);
        //m_cpu = new NesCpu(m_cpuBus);
        //m_ppu = new NesPpu(m_ppuBus);

        //m_apu->start();
        //m_cpu->start();
        //m_ppu->start();

        m_state = NesEmuState::PLAYING;

        if (m_logEnabled) {
            enableLog(m_logFlags); //Enable the log for the components.
        }

    }

    void NesEmu::stop()
    {
        m_state = NesEmuState::STOPPED;

        //Debugging.
        if (m_logEnabled) {
            *m_logStream << "Emu:\t Stopping..." << std::endl;
        }

        if (m_state != NesEmuState::STOPPED) {
            //m_apu->stop();
            //m_cpu->stop();
            //m_ppu->stop();
        }   

        //delete m_apu;
        //delete m_cpu;
        //delete m_ppu;
        delete m_ram;
        //delete m_rom;
        //delete m_vram;
        //delete m_apuBus;
        delete m_cpuBus;
        //delete m_ppuBus;
        delete m_controller1;
        delete m_controller2;
    }


    //Saving
    void NesEmu::load(std::istream& saveStream)
    {
        //Debugging
        if (m_logEnabled) {
            *m_logStream << "Emu:\t Loading..." << std::endl;
        }

        if (m_state != NesEmuState::STOPPED) {
            //m_apu->load(saveStream);
            //m_cpu->load(saveStream);
            //m_ppu->load(saveStream);
            m_ram->load(saveStream);
            //m_vram->load(saveStream);
        }
    }

    void NesEmu::save(std::ostream& saveStream)
    {
        //Debugging
        if (m_logEnabled) {
            *m_logStream << "Emu:\t Saving..." << std::endl;
        }

        if (m_state != NesEmuState::STOPPED) {
            //m_apu->save(saveStream);
            //m_cpu->save(saveStream);
            //m_ppu->save(saveStream);
            m_ram->save(saveStream);
            //m_vram->save(saveStream);
        }
    }


    //Debugging
    void NesEmu::enableLog(uint16_t flags)
    {
        m_logEnabled = true;
        m_logFlags = (LogFlags)(m_logFlags | flags);

        if (m_state != NesEmuState::STOPPED) {
            //if (flags & LogFlags::LOG_APU) m_apu->enableLog();
            //if (flags & LogFlags::LOG_CPU) m_cpu->enableLog();
            //if (flags & LogFlags::LOG_PPU) m_ppu->enableLog();
            if (flags & LogFlags::LOG_RAM)  m_ram->enableLog();
            //if (flags & LogFlags::LOG_ROM) m_rom->enableLog();
            //if (flags & LogFlags::LOG_VRAM) m_vram->enableLog();
            //if (flags & LogFlags::LOG_BUS) m_apuBus->enableLog();
            if (flags & LogFlags::LOG_BUS) m_cpuBus->enableLog();
            //if (flags & LogFlags::LOG_BUS) m_ppuBus->enableLog();
            if (flags & LogFlags::LOG_JOY1) m_controller1->enableLog();
            if (flags & LogFlags::LOG_JOY2) m_controller2->enableLog();
        }
    }

    void NesEmu::disableLog(uint16_t flags)
    {
        m_logEnabled = false;
        m_logFlags = (LogFlags)(m_logFlags & ~flags);

        if (m_state != NesEmuState::STOPPED) {
            //if (flags & LogFlags::LOG_APU) m_apu->disableLog();
            //if (flags & LogFlags::LOG_CPU) m_cpu->disableLog();
            //if (flags & LogFlags::LOG_PPU) m_ppu->disableLog();
            if (flags & LogFlags::LOG_RAM)  m_ram->disableLog();
            //if (flags & LogFlags::LOG_ROM) m_rom->disableLog();
            //if (flags & LogFlags::LOG_VRAM) m_vram->disableLog();
            //if (flags & LogFlags::LOG_BUS) m_apuBus->disableLog();
            if (flags & LogFlags::LOG_BUS) m_cpuBus->disableLog();
            //if (flags & LogFlags::LOG_BUS) m_ppuBus->disableLog();
            if (flags & LogFlags::LOG_JOY1) m_controller1->disableLog();
            if (flags & LogFlags::LOG_JOY2) m_controller2->disableLog();
        }
    }

    void NesEmu::setLogStream(std::ostream& logStream)
    {
        m_logStream = &logStream;
        if (m_state != NesEmuState::STOPPED) {
            //m_apu->setLogStream(logStream);
            //m_cpu->setLogStream(logStream);
            //m_ppu->setLogStream(logStream);
            m_ram->setLogStream(logStream);
            //m_rom->setLogStream(logStream);
            //m_vram->setLogStream(logStream);
            //m_apuBus->setLogStream(logStream);
            m_cpuBus->setLogStream(logStream);
            //m_ppuBus->setLogStream(logStream);
            m_controller1->setLogStream(logStream);
            m_controller2->setLogStream(logStream);
        }
    }

}

