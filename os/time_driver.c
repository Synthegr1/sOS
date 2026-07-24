#include "util.h"
#include "kernel.h"

#define O 35

int subsec;
int seconds;
int min;
int hour;
int day;
int mounth;
int year;

int seconds_adress = 0x00;
int min_adress = 0x02;
int hour_adress = 0x04;
int day_adress = 0x07;
int mounth_adress = 0x08;
int year_adress = 0x09;

int color_af_hour = 0x0F;

int ps;

int bcd_to_bin(unsigned char bcd) {
    return ((bcd / 16) * 10) + (bcd % 16);
}

unsigned char rtc_read_port(int reg){
    outb(0x70, reg);
    return inb(0x71);
}

unsigned char pit_read_port(){
    return inb(0x40);
}

void rtc_read_and_class() {
    subsec = bcd_to_bin(pit_read_port());
    seconds = bcd_to_bin(rtc_read_port(seconds_adress));
    min     = bcd_to_bin(rtc_read_port(min_adress));
    hour    = bcd_to_bin(rtc_read_port(hour_adress));
    day     = bcd_to_bin(rtc_read_port(day_adress));
    mounth  = bcd_to_bin(rtc_read_port(mounth_adress));
    year    = bcd_to_bin(rtc_read_port(year_adress));
}

void hour_fn(){
    char hour_c[32];
    char min_c[32];
    char sec_c[32];
    rtc_read_and_class();
    convertIntTOChar(hour + 4, hour_c);
    convertIntTOChar(min, min_c);
    convertIntTOChar(seconds, sec_c);
    print_at(hour_c, 0, posdeb + 1, 0x01);   
    print_at(":", 2, posdeb + 1, 0x01);   
    print_at(min_c, 3, posdeb + 1, 0x01);  
    print_at(":", 5, posdeb + 1, 0x01);
    print_at(sec_c, 6, posdeb + 1, 0x01);         
    
}
    int o = O;
    int ps = O + 6;
    int b = 0;

void hour_fn_const(){
    char hour_c[32];
    char min_c[32];
    char sec_c[32];
    char ssec_c[32];

    int base_x = O;        
    int sec_x  = base_x + 6;

    rtc_read_and_class();
    convertIntTOChar(hour + 2, hour_c);
    convertIntTOChar(min, min_c);
    convertIntTOChar(seconds, sec_c);
    convertIntTOChar(subsec, ssec_c);
    print_at(hour_c, O, 1, color_af_hour);   
    print_at(":", 2 + O, 1, color_af_hour);   
    print_at(min_c, 3 + O, 1, color_af_hour);  
    print_at(":", 5 + O, 1, color_af_hour);   
    
    if(seconds < 10){
        print_at("0", sec_x, 1, color_af_hour);   // leading zero
        print_at(sec_c, sec_x + 1, 1, color_af_hour);
    } else {
        print_at(sec_c, sec_x, 1, color_af_hour);
    }
     
    print_at(":", 8 + O, 1, color_af_hour); 
    print_at(ssec_c, 9 + O, 1, color_af_hour);  
    

    if(seconds < 10){
        if(b == 0){
            ps += 1;
        }
        //print_at("brrjrh", 14, 14, 0x90);
    } else {
        ps = O;
        b = 1;
    }
}