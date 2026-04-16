#include "draw.h"

void flushScreen(void *xfb, GXRModeObj *rmode)
{
    VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_BLACK);
}

void drawPixel(u32 x, u32 y, const u32 color, u32* xfb)
{
    x >>= 1;
    y *= 320;

    xfb[x+y] = color;
}

void drawHLine(u32 x1, u32 x2, u32 y, const u32 color, u32* xfb)
{
    y = 320 * y;
    x1 >>= 1;
    x2 >>= 1;
    for (u32 i = x1; i <= x2; i++) {
        u32* tmpfb = xfb;
        tmpfb[y+i] = color;
    }
}

void drawVLine(const u32 y1, const u32 y2, u32 x, const u32 color, u32* xfb)
{
    x >>= 1;
    for (u32 i = y1; i <= y2; i++) {
        u32* tmpfb = xfb;
        tmpfb[x + (640 * i) / 2] = color;
    }
}

void drawBox(const u32 x1, const u32 y1, const u32 x2, const u32 y2, const u32 color, u32* xfb)
{
    drawHLine(x1, x2, y1, color, xfb);
    drawHLine(x1, x2, y2, color, xfb);
    drawVLine(y1, y2, x1, color, xfb);
    drawVLine(y1, y2, x2, color, xfb);
}