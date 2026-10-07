#include "kernel.h"
#include "util.h"

int get_cpu_temp(){
    unsigned long long therm = rdmsr(0x19C);
    // Extrait la température : bits [22:16]
    unsigned int readout = (therm >> 16) & 0x7F;

    // Là, tu as un nombre entre 0 et 127 → ça tient dans un int
    int temp = 100 - (int)readout;   

    return temp;  // renvoie un int (ex: 45 pour 45°C)
}

void hard_infos(){
    char cpu_c[32];

    convertIntTOChar(get_cpu_temp(), cpu_c);

    print_at("CPU TEMP : ", 1, 24, 0x0F);
    print_at(cpu_c, 12, 24, 0x0F);
}