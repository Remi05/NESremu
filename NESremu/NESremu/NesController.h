#pragma once
#include <cstdint>

namespace NESremu
{
    class NesController
    {
        enum NesButtons
        {
            BUTTON_A = 0x01,
            BUTTON_B = 0x02,
            BUTTON_SELECT = 0x04,
            BUTTON_START = 0x08,
            BUTTON_UP = 0x10,
            BUTTON_DOWN = 0x20,
            BUTTON_LEFT = 0x40,
            BUTTON_RIGHT = 0x80
        };

        //uint8_t Controller1 = 0;
        //uint8_t Controller2 = 0;
    };
}
