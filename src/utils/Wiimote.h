#pragma once

#include <utility>
#include <stdexcept>

#include <wiiuse/wpad.h>

class Wiimote
{
    int channel {};

    ir_t ir      {};
    u32  pressed {};
    u32  held    {};
    u32  released{};
public:
    explicit Wiimote(int channel);

    void scanInput();
    [[nodiscard]] std::pair<float, float> getCursorPos() const { return {ir.x, ir.y}; }

    [[nodiscard]] bool isPressed (const int button) const { return pressed  & button; }
    [[nodiscard]] bool isHeld    (const int button) const { return held     & button; }
    [[nodiscard]] bool isReleased(const int button) const { return released & button; }
};

class Wiimotes
{
    Wiimote wiimotes[4];
public:
    Wiimotes(): wiimotes{ Wiimote(0), Wiimote(1), Wiimote(2), Wiimote(3) } {}
    
    void scanInput();

    const Wiimote& operator[](const int channel) const
    {
        return wiimotes[std::min(std::max(channel, 0), 3)];
    }
};