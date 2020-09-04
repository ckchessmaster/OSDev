#include "kernel_io.h"

extern char framebuffer;
extern BOOTBOOT bootboot; 

KernelFont KernelIO::font;
int KernelIO::cursorX = 0;
int KernelIO::cursorY = 0;
int KernelIO::foreground = 0x00FF00;
int KernelIO::background = 0x000000;

void KernelIO::init() {
    font = KernelFont();
}

void KernelIO::print(const char* string) {
    unsigned int byptesPerLine = font.getBytesPerLine();
    unsigned int fontWidth = font.getWidth();
    unsigned int fontHeight = font.getHeight();
    unsigned int scanline = bootboot.fb_scanline;
    unsigned int maxHeight = bootboot.fb_height;

    while (*string != '\0') {
        int x, y, mask;
        unsigned int offset, offsetX, line;

        if(cursorY * (fontHeight * 4) > maxHeight) {
            cursorY--;
            unsigned int* moveStart = ((unsigned int*)&framebuffer + scanline + (scanline * fontHeight));
            size_t length = sizeof(char) * scanline * (fontHeight) * cursorY;
            memmove((&framebuffer + scanline), moveStart, length);
        } 

        if(*string == '\n') {
            cursorY++;
            cursorX = 0;
            string++;
            continue;
        }

        offsetX = cursorX * fontWidth * 4;

        if (offsetX + fontWidth > scanline) {
            cursorY++;
            cursorX = 0;
        }

        offset = (cursorX * fontWidth * 4) + (cursorY * fontHeight * scanline * 2);
        unsigned char* glyph = font.getGlyph(*string);

        // Draw the glyph
        for(y=0; y<fontHeight; y++) {
            line = offset;
            mask = 1 << (fontWidth - 1);

            for(x=0; x<fontHeight; x++) {
                *((unsigned int*)(&framebuffer + offset + (x * 4) + (y * scanline))) = ((int)*glyph) & (mask) ? foreground : background;
                mask >>= 1;
                line += 4;
            }

            *((unsigned int*)(&framebuffer + offset + (x * 4) + (y * scanline))) = 0;
            glyph += byptesPerLine; 
            offset += scanline;
        }

        string++;
        cursorX++;
    }
}

void KernelIO::error(const char* string) {
    int x, y;

    int scanline = bootboot.fb_scanline;
    int maxHeight = bootboot.fb_height;

    foreground = 0x00000000;
    background = 0x00FF0000;

    cursorX = 0;
    cursorY = 0;

    for(y=0; y<maxHeight; y++) {
        for(x=0; x<scanline; x++) {
            *((unsigned int*)(&framebuffer + (x * 4) + (y * scanline))) = 0x00FF0000;   
        }
    }

    print(string);
}