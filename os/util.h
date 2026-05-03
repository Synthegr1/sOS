#ifndef UTIL_H
#define UTIL_H

// --- Convertion char vers int --- //
int convertCharToInt(char t[3]);

// --- Convertion int vers char --- //
void convertIntTOChar(int u, char *str);

// --- Comparation de deux chaînes de charactères --- //
int compchar(char *a, char *b);

// --- Taille d'un char --- //
int sizeOf(char *input);

// --- Vérification qu'un chaine de charactères commencent par [x] --- //
int startsWith(char *a, char *b);

// --- Fonction utile a convertIntTOChar() --- //
int get_digit(int m, int n);

// --- Calculer la taille d'un dico de int --- //
int sizeIntOf(int *input);

void clearBuffer(char *h);

int is_decimal(char *input);

double convertCharToDecimal(char *t);

void convertDecimalToChar(double number, char *str);

#endif