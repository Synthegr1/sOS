#include <stdio.h>

int n = 0;

void convertIntToChar(int d, char *str){
    // Gestion du cas 0
    if (d == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    int n = 0;          // n doit être local, pas global
    int temp = d;
    
    // Compte le nombre de chiffres
    while(temp >= 10){
        temp /= 10;
        n++;
    }
    
    // Extraction des chiffres de droite à gauche
    for(int i = n; i >= 0; i--){
        str[i] = '0' + (d % 10);  // dernier chiffre
        d /= 10;                   // on enlève le dernier chiffre
    }
    
    str[n + 1] = '\0';  // terminateur de chaîne
}

void main(){
    char str[10];
    int t = 6789696;
    convertIntToChar(t, str);
    printf("%s\n", str);
    printf("%d\n", n);
}