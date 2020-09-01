#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bootboot.h>
#include "kernel.h"

/* imported virtual addresses, see linker script */
extern BOOTBOOT bootboot;               // see bootboot.h
extern unsigned char environment[4096]; // configuration, UTF-8 text key=value pairs
extern char framebuffer;                // linear framebuffer mapped

/******************************************
 * Entry point, called by BOOTBOOT Loader *
 ******************************************/
void _start() {
    /*** NOTE: this code runs on all cores in parallel ***/
    int x, y, scanline=bootboot.fb_scanline, maxWidth=bootboot.fb_width, maxHeight=bootboot.fb_height;

    // cross-hair to see screen dimension detected correctly
    for(y=0; y<maxHeight; y++) { 
        *((unsigned int*)(&framebuffer + scanline * y + (maxWidth * 2))) = 0xFFFFFF; 
    }
    
    for(x=0; x<maxWidth; x++) { 
        *((unsigned int*)(&framebuffer + scanline * (maxHeight / 2) + x * 4)) = 0xFFFFFF; 
    }

    print("01234567890 the quick brown fox jumps over the lazy dog!");

    // OS Loop
    while(1);
}

#define PSF_FONT_MAGIC 0x864ab572
typedef struct {
    uint32_t magic;         /* magic bytes to identify PSF */
    uint32_t version;       /* zero */
    uint32_t headersize;    /* offset of bitmaps in file, 32 */
    uint32_t flags;         /* 0 if there's no unicode table */
    uint32_t numglyph;      /* number of glyphs */
    uint32_t bytesperglyph; /* size of each glyph */
    uint32_t height;        /* height in pixels */
    uint32_t width;         /* width in pixels */
} __attribute__((packed)) Font;

extern volatile unsigned char _binary_font_psf_start;

int foreground = 0x00FF00;
int background = 0x000000;

void print(char const *s) {
    Font *font = (Font*)&_binary_font_psf_start;
    int x, y, line, mask, offset;
    int byptesPerLine = (font->width + 7) /8;
    int kx = 0;

    while(*s) {
        unsigned char *glyph = (unsigned char*)&_binary_font_psf_start + font->headersize + (*s > 0 && *s < font->numglyph ? *s : 0) * font->bytesperglyph;
        offset = (kx * (font->width + 1) * 4);
        
        for(y=0; y<font->height; y++) {
            line = offset;
            mask = 1 << (font->width - 1);

            for(x=0; x<font->width; x++) {
                *((unsigned int*)((unsigned long int)&framebuffer + line)) = ((int)*glyph) & (mask) ? foreground : background;
                mask >>= 1;
                line += 4;
            }

            *((unsigned int*)((unsigned long int)&framebuffer + line)) = 0; 
            glyph += byptesPerLine; 
            offset += bootboot.fb_scanline;
        }

        s++; 
        kx++;
    }
}
