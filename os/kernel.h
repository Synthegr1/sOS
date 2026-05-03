#ifndef KERNEL_H
#define KERNEL_H

int print_at(const char* input, int x, int y, int color);
void bureau();
void clear();
static inline unsigned char inb(unsigned short port);
static inline void outw(unsigned short port, unsigned short val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

extern int echocolor;
extern int posdeb;

#endif