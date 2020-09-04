#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bootboot.h>

#include "kernel_io.h"
#include "libc/string.h"

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
    //KernelIO::print("Hello World!\n");
    //KernelIO::error("Error!!!!");

    KernelIO::print("I'm going to go away soon :(\n");

    for(int x=0; x<23; x++) {
        KernelIO::print("A\n");
    }

    KernelIO::print("I havn't show up yet! :o\n");

    // OS Loop
    while(1);
}

extern "C" void __cxa_pure_virtual()
{
    KernelIO::error("Pure virtual function call!");
}
