#ifndef MATH_H
#define MATH_H

// --- Puissance d entiers --- //
int square(int number, int p);

// --- Arrondir au dixieme --- //
float round_1d(float f);

// --- Arrondir au centieme --- //
float round_2d(float f);

// --- Logarithme base e --- //
float ln(float x);

// --- Exponentielle --- //
float exp(float x);

// --- Puissance de float --- //
float pow(float x, float y);

// --- Logarithme base 10 --- //
float logb10(float x);

// --- Avoir le premier chiffre d'un nombre --- //
int get_first_significant_digit(int x);

// --- Avoir le deuxième chiffre d'un nombre --- //
int get_second_significant_digit(float x);

// --- Avoir le troisième chiffre d'un nombre --- //
int get_third_significant_digit(float x);

// --- Connatre la taille (nombres de caractères) d'un nombre --- //
int get_number_size(int x);

// --- Avoir le quatrième chiffre d'un nombre --- //
int get_fourth_significant_digit(float x);

// --- Avoir le cinquième chiffre d'un nombre --- //
int get_fifth_significant_digit(float x);

int get_first_decimal(double x);

int get_second_decimal(double x); 

int get_third_decimal(double x);

int get_fourth_decimal(double x);

#endif
