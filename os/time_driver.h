#ifndef TIME_H
#define TIME_H

extern int subsec;
extern int seconds;
extern int min;
extern int hour;
extern int day;
extern int mounth;
extern int year;

extern int color_af_hour;

unsigned char rtc_read_port(int reg);
void rtc_read_and_class();
void hour_fn_const();
void hour_fn();

#endif