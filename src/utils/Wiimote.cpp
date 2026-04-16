#include "Wiimote.h"

Wiimote::Wiimote(const int channel)
{
    this->channel = std::min(std::max(channel, 0), 3);

    WPAD_SetVRes(channel, 640, 480);
    WPAD_SetDataFormat(channel, WPAD_FMT_BTNS_ACC_IR);
}

void Wiimote::scanInput() 
{
    WPAD_IR(channel, &ir);
    pressed  = WPAD_ButtonsDown(channel);
    held     = WPAD_ButtonsHeld(channel);
    released = WPAD_ButtonsUp  (channel);
}

void Wiimotes::scanInput() 
{ 
    WPAD_ScanPads();

    for (auto& wiimote : wiimotes)
        wiimote.scanInput();
}