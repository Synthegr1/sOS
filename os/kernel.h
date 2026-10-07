#ifndef KERNEL_H
#define KERNEL_H

int print_at(const char* input, int x, int y, int color);
void bureau();
void clear();


//Fonction pour intteroger un port processeur (port)

//unsigned char = 8 bits & unsigned short = 16 bits
static inline unsigned char inb(unsigned short port) {
    unsigned char val; //On définit val comme ce qui sera la réponse du port
    asm volatile ("inb %1, %0" : "=a"(val) : "Nd"(port)); //On demande au processeur avec 'asm'
    return val; //On retourne 'asm'
}

static inline void outb(unsigned short port, unsigned char val) { // Récupération de la valeur des ports 8 bits (char)
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline void outw(unsigned short port, unsigned short val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned long long rdmsr(unsigned int msr) {
    unsigned int low, high;
    __asm__ __volatile__("rdmsr" : "=a"(low), "=d"(high) : "c"(msr));
    return ((unsigned long long)high << 32) | low;
}

extern int echocolor;
extern int posdeb;

#endif