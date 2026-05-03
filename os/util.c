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
    int q = (int) number;
    convertIntTOChar(q, str);
    str[get_number_size(q)] = ',';
    int u = get_number_size(q) + 1;
    double m = number - q;
    while (m < 1) {
        m *= 10;
    }
    int o = (int) m;
    char txt[10];
    convertIntTOChar(o, txt);
    int y = 0;
    for (int i = u; i < sizeOf(str) + sizeOf(txt); i++) {
        str[i] = txt[y];
        y += 1;
    }
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

    int size = get_number_size(u);

    int numbers[size];

    int t = 0;

    for (int f = 0; f < size; f++) {
        numbers[f] = get_digit(f + 1, u);
    }

    for(int cursor = 0; cursor < size; cursor ++){
        t = numbers[cursor];

        switch (t){
            case 0:
                str[cursor] = '0';
                break;
            case 1:
                str[cursor] = '1';
                break;
            case 2:
                str[cursor] = '2';
                break;
            case 3:
                str[cursor] = '3';
                break;
            case 4:
                str[cursor] = '4';
                break;
            case 5:
                str[cursor] = '5';
                break;
            case 6:
                str[cursor] = '6';
                break;
            case 7:
                str[cursor] = '7';
                break;
            case 8:
                str[cursor] = '8';
                break;
            case 9:
                str[cursor] = '9';
                break;
            default:
                str[cursor] = 'x';
                break;
            }

    }
    str[size] = '\0';
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
