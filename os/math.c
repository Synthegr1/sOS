#include "math.h"

// --- Puissance d entiers --- //
int square(int number, int p){
    int result = number;
    if (p == 0) {
        result = 1;
        return result;
    } else {
        for(int i = 1; i < p; i++){
            result = result * number;
        }
        return result;
    }
}

// --- Arrondir au dixieme --- //
float round_1d(float f){
    if(f > 0){
        float t = f * 10;
        float h = (int)(t);
        return h / 10;
    }
}

// --- Arrondir au centieme --- //
float round_2d(float f){
    if(f > 0){
        float t = f * 100;
        float h = (int)(t + 0.5f);
        return h / 100;
    }
}

// --- Logarithme base e --- //
float ln(float x){
    float u = (x - 1.0f) / (x + 1.0f);
    float u2 = u * u;
    float terme = u;
    float resultat = terme;

    for (int n = 1; n < 100; n++) {
        terme = terme * u2;
        resultat = resultat + terme / (2*n + 1);
    }

    return 2.0f * resultat;

}

// --- Exponentielle --- //
float exp(float x) {
    float resultat = 1.0f;
    float terme    = 1.0f;

    for (int n = 1; n < 150; n++) {
        terme = terme * x / (float)n;
        resultat = resultat + terme;
    }

    return resultat;
}

// --- Puissance de float --- //
float pow(float x, float y) {
    return exp(y * ln(x));
}

//Logarithme base 10
float logb10(float x){
    return ln(x) / ln(10.0f);
}

// --- Logarithme base 10 --- //
int get_first_significant_digit(int x){
    while (x > 10) {
        x /= 10;
    }
    return (int) x;
}

// --- Avoir le deuxième chiffre d'un nombre --- //
int get_second_significant_digit(float x){
    while(x >= 10){
        x = x / 10;
    }
    int o = (int)(x);
    x = x - o;
    x *= 10;
    return (int)(x);
}

// --- Avoir le troisième chiffre d'un nombre --- //
int get_third_significant_digit(float x){
    while(x >= 100){
        x = x / 10;
    }
    int o = (int)(x);
    float t = x - o;
    t *= 10;
    return (int)(t);
}

// --- Avoir le quatrième chiffre d'un nombre --- //
int get_fourth_significant_digit(float x){
    while(x >= 10){
        x = x / 10;
    }
    x *= 100;
    int o = (int)(x);
    x = x - o;
    x *= 10;
    return (int)(x);
}

// --- Avoir le cinquième chiffre d'un nombre --- //
int get_fifth_significant_digit(float x){
    while(x >= 10){
        x /= 10;
    }
    x = x * square(10, 3);
    int o = (int)(x);
    x = x - o;
    return (int)(x * 10);
}

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

int get_third_decimal(double x) {
    x *= 100;
    int t = (int)(x);
    double i = x - t;
    while (i < 1) {
        i *= 10;
    }
    return (int)(i);
}

int get_fourth_decimal(double x) {
    x *= 1000;
    int t = (int)(x);
    double i = x - t;
    while (i < 1) {
        i *= 10;
    }
    return (int)(i);
}

// --- Connatre la taille (nombres de caractères) d'un nombre --- //
int get_number_size(int x){
    float f = x;
    int count = 1;
    while(f >= 10){
        count += 1;
        f /= 10;
    }
    return count;
}
