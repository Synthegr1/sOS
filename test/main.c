#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int get_first_decimal(double x) {
    int t = (int)(x);
    double i = x - t;
    while (i < 1) {
        i *= 10;
    }
    return (int)(i);
}

int get_second_decimal(double x) {
    x *= 10;
    int t = (int)(x);
    double i = x - t;
    while (i < 1) {
        i *= 10;
    }
    return (int)(i);
}

int main(){
    int x = 12;
    double f = x;

    printf("%d\n", get_second_decimal(78.325));
    return 0;
}