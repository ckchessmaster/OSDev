#include "kernel_font.h"

KernelFont::KernelFont() {
    this->font = (Font*)&_binary_font_psf_start;
}

unsigned char* KernelFont::getGlyph(char c) {
    return (unsigned char*)&_binary_font_psf_start + font->headersize + (c > 0 && c < font->numglyph ? c : 0) * font->bytesperglyph;
}

unsigned int KernelFont::getBytesPerLine() {
    return (font->width + 7) /8;
}

unsigned int KernelFont::getHeight() {
    return font->height;
}

unsigned int KernelFont::getWidth() {
    return font->width;
}