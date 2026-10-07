#include "util.h"
#include "math.h"

//Fonction pour connaitre le lenght d un char (nmb de caractères)
int sizeOf(char *input){
    int i = 0;
    while(input[i] != '\0'){
        i++;
    }
    return i;
}

// --- Calculer la taille d'un dico de int --- //
int sizeIntOf(int *input) {
    int i = 0;
    while(input [i] != 524852) {
        i++;
    }
    return i;
}

// --- Convertion int vers char --- //
int convertCharToInt(char *t){
    int size = sizeOf(t);
    int temp[size + 1];

    for(int x = 0; x < size; x++){
        switch(t[x]){
            case '0':
                temp[x] = 0;
                break;
            case '1':
                temp[x] = 1;
                break;
            case '2':
                temp[x] = 2;
                break;
            case '3':
                temp[x] = 3;
                break;
            case '4':
                temp[x] = 4;
                break;
            case '5':
                temp[x] = 5;
                break;
            case '6':
                temp[x] = 6;
                break;
            case '7':
                temp[x] = 7;
                break;
            case '8':
                temp[x] = 8;
                break;
            case '9':
                temp[x] = 9;
                break;
            default:
                return 13;
                break;
        }
    }
    temp[size] = 524852;
    int f = sizeIntOf(temp);
    int result = 0;
    for (int x = 0; x < sizeIntOf(temp); x++){
        f -= 1;
        result = (result + (temp[x] * square(10, f)));
    }
    return result;
}

char before[10];
char after[10];

void convertDecimalToChar(double number, char *str) {
    int f = (int)number;   
    double aft = number - f;
    int x = 0;
    int o = 0;
    char be[10];
    char af[10];
    char to[10];

    convertIntTOChar(f, be);
    convertIntTOChar((int)aft * 10000, af);
    
    while(be[x] != '\0'){
        to[x] = be[x];
        x += 1;
    }

    to[x] = '\0';
    x += 1;

    while(af[o] != '\0'){
        to[x] = af[o];
        x += 1;
        o += 1;
    }

    to[x] = '\0';
    int i = 0;
    while (to[i] != '\0') {
        str[i] = to[i];
        i++;
    }
    str[i] = '\0';
}

double convertCharToDecimal(char *t) {
    clearBuffer(before);
    clearBuffer(after);

    int size = sizeOf(t);
    int curs = 0;
    int f = 0;
    int o = 0;

    if (is_decimal(t) == 1) {
        for (int i = 0; i < size; i++) {
            if (t[i] != ',' && t[i] != '.') {
                f += 1;
                before[f] = t[i];
            } else if (t[i] == ',' && t[i] == '.') {
                o += 1;
                before[f] = '\0';
                after[o] = t[i];
            }
        }
        after[o] = '\0';

        int p = convertCharToInt(before);
        int u = convertCharToInt(after);

        double m = u;

        while (m > 1) {
            m /= 10;
        }

        double result = p + m;
        return result;
    }
}

int is_decimal(char *input) {
    int size = sizeOf(input);
    int is_an_decimal = 0;

    for(int x = 0; x < size; x++) {
        if (input[x] == ',' || input[x] == '.') {
            is_an_decimal = 1;
        }
    }

    return is_an_decimal;
}

int get_digit(int m, int n) {
    switch(m) {
        case 1:
            return get_first_significant_digit(n);
            break;
        case 2:
            return get_second_significant_digit(n);
            break;
        case 3:
            return get_third_significant_digit(n);
            break;
        case 4:
            return get_fourth_significant_digit(n);
            break;
        case 5:
            return get_fifth_significant_digit(n);
            break;
        default:
            return 404;
    }
}

int get_decimal(int m, int n) {
    switch(m) {
        case 1:
            return get_first_decimal(n);
            break;
        case 2:
            return get_second_decimal(n);
            break;
        case 3:
            return get_third_decimal(n);
            break;
        case 4:
            return get_fourth_decimal(n);
            break;
        default:
            return 404;
            break;
    }
}

//Fonction convert Int to Char
void convertIntTOChar(int u, char *str){
        // Gestion du cas 0
    if (u == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    int n = 0;          // n doit être local, pas global
    int temp = u;
    
    // Compte le nombre de chiffres
    while(temp >= 10){
        temp /= 10;
        n++;
    }
    
    // Extraction des chiffres de droite à gauche
    for(int i = n; i >= 0; i--){
        str[i] = '0' + (u % 10);  // dernier chiffre
        u /= 10;                   // on enlève le dernier chiffre
    }
    
    str[n + 1] = '\0';  // terminateur de chaîne
}

//Fonction de comparation de 2 char char1 = char2 ?
int compchar(char *a, char *b){
    int curs = 0;
    while(a[curs] != '\0' && b[curs] != '\0'){
        if(a[curs] != b[curs]){
            return 0; //Différent, return false (0)
        }
        curs++;
    }
    return 1; //Identique, return true (1)
}

//Fonction pour voir si 2 chars commencent pareil
int startsWith(char *a, char *b){
    int curs = 0;
    int firtchars = 0;

    while(a[curs] != '\0' && b[curs] != '\0'){ //Tant qu'il reste des caractères
        if(a[curs] != b[curs]){ //Si 2 caractères sont différents
            if(firtchars >= 4){ //Est ce qu ils sont différent mais autres que les 4 premiers caractères?
                return 1; //Oui, leurs 4 premiers char sont identiques, return true (1)
            } else {
                return 0; //Non, return false (0)
            }
        } else {
            firtchars += 1; //On continue de monter le curseur de début
        }
        curs++; //On augmente le curseur
    }
    return 1; //On retourne par défaut true (1) si il y a un probleme
}

void clearBuffer(char *h){
    int size = sizeOf(h);
    for(int i = 0; i < size; i++){
        h[i] = '\0';
    }
}

char* fus_char(char *a, char *b){
    int sia = sizeOf(a);
    int sib = sizeOf(b);
    char f[sia + sib];

    for(int i = 0; i < sia; i++){
        f[i] = a[i];
    }
    int x = 0;
    for(int i = sia; i < sia + sib; i++){
        f[i] = b[x];
        x += 1;
    }
    return f;
}
