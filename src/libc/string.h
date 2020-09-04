#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
 
void* memmove(void* dest, const void* src, size_t n);
void* memcpy(void* dest, const void* src, size_t n);
size_t strlen(const char* str);

#ifdef __cplusplus
}
#endif
 

#endif