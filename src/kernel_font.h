#ifndef _KERNEL_FONT_H_
#define _KERNEL_FONT_H_

#include <stdint.h>

#define PSF_FONT_MAGIC 0x864ab572
typedef struct {
    unsigned int magic;         /* magic bytes to identify PSF */
    unsigned int version;       /* zero */
    unsigned int headersize;    /* offset of bitmaps in file, 32 */
    unsigned int flags;         /* 0 if there's no unicode table */
    unsigned int numglyph;      /* number of glyphs */
    unsigned int bytesperglyph; /* size of each glyph */
    unsigned int height;        /* height in pixels */
    unsigned int width;         /* width in pixels */
} __attribute__((packed)) Font;

extern volatile unsigned char _binary_font_psf_start;

class KernelFont {
    private:
        Font* font;

    public:
        KernelFont();

        unsigned char* getGlyph(char c);

        unsigned int getBytesPerLine();
        unsigned int getHeight();
        unsigned int getWidth();
};

#endif