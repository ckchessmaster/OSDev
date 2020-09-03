#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bootboot.h>

#include "kernel_io.h"

/* imported virtual addresses, see linker script */
extern BOOTBOOT bootboot;               // see bootboot.h
extern unsigned char environment[4096]; // configuration, UTF-8 text key=value pairs
extern char framebuffer;                // linear framebuffer mapped

/******************************************
 * Entry point, called by BOOTBOOT Loader *
 ******************************************/
void _start() {
    /*** NOTE: this code runs on all cores in parallel ***/   

    KernelIO::init();
    KernelIO::print("Hello World!\n");
    //KernelIO::error("Error!!!!");

    // OS Loop
    while(1);
}
