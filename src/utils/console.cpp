#include "console.h"

#include <cstdio>
#include <cstdarg>

void printAt(const int x, const int y, const char *format, ...)
{
    // The console understands VT terminal escape codes
    // This positions the cursor on row 2, column 0
    // we can use variables for this with format codes too
    // e.g. printf ("\x1b[%d;%dH", row, column );
    printf("\x1b[%d;%dH", y, x);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
