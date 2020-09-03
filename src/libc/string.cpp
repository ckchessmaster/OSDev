#include <string.h>

void* memmove(void* dest, const void* src, size_t n) {
    for(int x=0; x<n; x++) {
        *((char*)dest + x) = *((char*)src + x);
    }

    return dest;
}

size_t strlen(const char* str) {
    size_t length = 0;

    while (*str != '\0') {
        length++;
    }

    return length;
}