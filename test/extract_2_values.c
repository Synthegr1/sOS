#include <stdio.h>
#include <string.h>

char firstchar[10];
char secondchar[10];

void extract_2_values(char *input){
    int f = 0;
    int y = 0;
    int who_is_it = 0;
    int charsize = strlen(input);
    for(int i = 0; i < charsize; i++){
        if(input[i] != ' '){
            if(who_is_it == 0){
                firstchar[i] = input[i];
            } else if(who_is_it == 1){
                secondchar[f] = input[i];
                f += 1;
            }
        } else if(input[i] == ' '){
            if(who_is_it == 0){
                firstchar[i] = '\0';
            }
            who_is_it = 1;
        }
        y = i;
    }
    secondchar[y] = '\0';
}

int main(){
    extract_2_values("56 6");
    printf("Value 1 : %s\n", firstchar);
    printf("Value 2 : %s\n", secondchar);
    return 0;
}