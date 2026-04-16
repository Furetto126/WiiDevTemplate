#pragma once

#include <gccore.h>

void flushScreen(void* xfb, GXRModeObj* rmode);
void drawPixel(u32 x, u32 y, u32 color, u32* xfb);

void drawHLine(u32 x1, u32 x2, u32 y, u32 color, u32* xfb);
void drawVLine(u32 y1, u32 y2, u32 x, u32 color, u32* xfb);
void drawBox  (u32 x1, u32 y1, u32 x2, u32 y2, u32 color, u32* xfb);