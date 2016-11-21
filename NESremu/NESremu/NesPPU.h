#pragma once
#include <cstdint>
#include "ILoggable.h"
#include "NesBus.h"

namespace nesremu
{
    class NesPpu : public ILoggable
    {
    private:
        ////PPU 16KiB memory bank (16384 bytes)
        //uint8_t  MemoryBank[0x4000];
        //uint8_t* PatternTable0 = MemoryBank;
        //uint8_t* PatternTable1 = MemoryBank + 0x1000; //$1000-$1FFF
        //uint8_t* Nametable0    = MemoryBank + 0x2000; //$2000-$23FF ($2000-$2EFF mirrored at $3000-$3EFF) 
        //uint8_t* Nametable1    = MemoryBank + 0x2400; //$2400-$27FF
        //uint8_t* Nametable2    = MemoryBank + 0x2800; //$2800-$2BFF
        //uint8_t* Nametable3    = MemoryBank + 0x2C00; //$2C00-$2FFF
        //uint8_t* PaletteRam    = MemoryBank + 0x3F00; //$3F00-$3F1F (mirrored at $3F20-$3FFF)
        //                                              //$3F00-$3F0F: Background palette, $3F10-$3F1F: Sprite palette

        //uint8_t ObjectAttributeMemory[0x100]; //Information for 64 sprites (4 bytes per sprite).
        ////Byte 0: Y position of the sprite.
        ////Byte 1: Tile index.
        ////Byte 2: Sprite attributes.
        ////Byte 3: X position of the left side of the sprite.

        NesBus* m_bus = nullptr;
        uint32_t m_ticks = 0;

        //Debugging
        bool m_logEnabled = false;
        std::ostream* m_logStream = &std::clog;


    public:
        NesPpu(NesBus* bus);
        ~NesPpu();

        //Core PPU functions.
        uint32_t getTicks();
        void load(std::istream& saveStream);
        void reset();
        void save(std::ostream& saveStream);
        void start();
        void stop();
        void tick();

        //Debugging
        virtual void enableLog()  { m_logEnabled = true;  }
        virtual void disableLog() { m_logEnabled = false; }
        virtual void setLogStream(std::ostream& logStream) { m_logStream = &logStream; }

    };
}