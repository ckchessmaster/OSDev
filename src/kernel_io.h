#ifndef _KERNEL_IO_H_
#define _KERNEL_IO_H_

#include <stdint.h>
#include <bootboot.h>

#include "kernel_font.h"
#include "libc/string.h"

class KernelIO {
    private:
        KernelIO();

        static KernelFont font;

        static int foreground;
        static int background;

        static int cursorX;
        static int cursorY;

    public:
        static void init();
        static void print(const char* string);
        static void error(const char* string);
};

#endif