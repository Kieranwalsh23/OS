
#include <stdint.h>
#include "portmap.h"


// Implementation of inb
uint8_t inb(unsigned short int port) {
    unsigned char ret;
    __asm__ __volatile__("inb %1, %0" : "=a" (ret) : "Nd" (port));
    return ret;
}

// Implementation of outb
void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__("outb %0, %1" : : "a" (val), "Nd" (port));
}