#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gccore.h>
#include <wiiuse/wpad.h>

#include "utils/init.h"
#include "utils/console.h"
#include "utils/draw.h"
#include "utils/Wiimote.h"

static u32 *xfb = NULL;
static GXRModeObj *rmode = NULL;

int main(int argc, char **argv)
{
    WiiVideoInit(&xfb, &rmode);
    Wiimotes wiimotes = Wiimotes();

    int frames = 1;
    int pointsInCircle = 0;
    double currentPI = 0.0;   

    srand(time(NULL));

    u32 x{}, y{};

    while (true)
    {
        flushScreen(xfb, rmode);

        // Call WPAD_ScanPads each loop, this reads the latest controller states
        wiimotes.scanInput();

        printAt(0, 2, "Hello World! Frame: %d", frames);

        {
            double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand() / RAND_MAX * 2.0 - 1.0;

            if (x * x + y * y <= 1.0)
                pointsInCircle++;
        }

        currentPI = 4.0 * (double)pointsInCircle / (double)frames;
        printAt(50, 2, "PI: %.6f", currentPI);

        if (wiimotes[0].isHeld(WPAD_BUTTON_A))
            flushScreen(xfb, rmode);

        // We return to the launcher application via exit
        if (wiimotes[0].isPressed(WPAD_BUTTON_HOME))
            exit(0);

        /*
        // X and Y coordinates with wrapping
        x = frames % 640;
        y = frames / 640;

        printAt(0, 5, "x = %d", x);
        printAt(0, 6, "y = %d", y);

        if (y < 480)
            drawPixel(x, y, COLOR_AQUA, xfb);
        */

        // Wait for the next frame
        VIDEO_WaitVSync();

        frames++;
        x++;
    }

    return 0;
}
