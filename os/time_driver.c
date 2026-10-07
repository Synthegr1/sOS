#include "util.h"
#include "kernel.h"

#define O 66

char date_c[32];

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

char* find_mounth(int i){
    switch (i)
    {
    case 1:
        return "January";
        break;
    case 2:
        return "February";
        break;
    case 3:
        return "March";
        break;
    case 4:
        return "April";
        break;
    case 5:
        return "May";
        break;
    case 6:
        return "June";
        break;
    case 7:
        return "July";
        break;
    case 8:
        return "August";
        break;
    case 9:
        return "September";
        break;
    case 10:
        return "October";
        break;
    case 11:
        return "November";
        break;
    case 12: 
        return "December";
        break;
    default:
        return "Mounth Error";
        break;
    }
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
    char year_c[32];
    char mounth_c[32];
    char day_c[32];

    int base_x = O;        
    int sec_x  = base_x + 6;
    int min_x = base_x + 3;

    rtc_read_and_class();
    convertIntTOChar(hour + 2, hour_c);
    convertIntTOChar(min, min_c);
    convertIntTOChar(seconds, sec_c);
    convertIntTOChar(subsec, ssec_c);
    print_at(hour_c, O, 2, color_af_hour);   
    print_at(":", 2 + O, 2, color_af_hour);   
    
    if(min < 10){
        print_at("0", min_x, 2, color_af_hour);   // leading zero
        print_at(min_c, min_x + 1, 2, color_af_hour);
    } else {
        print_at(min_c, min_x, 2, color_af_hour);
    }

    print_at(":", 5 + O, 2, color_af_hour);   
    
    if(seconds < 10){
        print_at("0", sec_x, 2, color_af_hour);   // leading zero
        print_at(sec_c, sec_x + 1, 2, color_af_hour);
    } else {
        print_at(sec_c, sec_x, 2, color_af_hour);
    }
     
    print_at(":", 8 + O, 2, color_af_hour); 
    print_at(ssec_c, 9 + O, 2, color_af_hour);  
    

    if(seconds < 10){
        if(b == 0){
            ps += 1;
        }
        //print_at("brrjrh", 14, 14, 0x90);
    } else {
        ps = O;
        b = 1;
    }

    //convertIntTOChar(mounth, mounth_c);
    convertIntTOChar(year + 2000, year_c);
    convertIntTOChar(day, day_c);

    int size = sizeOf(find_mounth(mounth));
    int ds = sizeOf(day_c);

    print_at(find_mounth(mounth), 1, 2, 0x0F);
    size += 2;
    print_at(day_c, size, 2, 0x0F);
    print_at(",", size + ds, 2, 0x0F);
    print_at(year_c, size + ds + 2, 2, 0x0F);
}