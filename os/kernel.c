void print_at(const char* input, int x, int y, int color){
    volatile char* video_memory = (volatile char*)0xb8000;

    int pos = (y * 80 + x) * 2;
    for(int i = 0; input[i] != '\0'; i++){
        video_memory[pos] = input[i];
        video_memory[pos + 1] = color;
        pos += 2;
    }
}
/*fonction du logo*/
void afficher_logo(void){
    print_at("           .d88888b.    .d8888b.", 24, 8, 0x0E);
    print_at("          d888P" "Y888b  d88P  Y88b", 24, 9, 0x0E);
    print_at("         888     888  Y88b.", 24, 10, 0x0E);
    print_at(".d8888b  888     888   \"Y888b.", 24, 11, 0x0E);
    print_at("88K      888     888      \"Y88b.", 24, 12, 0x0E);
    print_at("\"Y8888b. 888     888        \"888", 24, 13, 0x0E);
    print_at("     X88 Y88b. .d88P  Y88b  d88P", 24, 14, 0x0E);
    print_at(" 88888P'  \"Y88888P\"    \"Y8888P\"", 24, 15, 0x0E);
}
/*fonction de clear de l'écran*/
void clear(){
    volatile char* video_memory = (volatile char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i+1] = 0x07;
    }
}
/*bureau*/
void bureau(){
    clear();
    print_at("voici le Bureau", 24, 8, 0x0E);
    while(1);
}

/*fonction principale*/
void main() {
    clear();
    afficher_logo();
    bureau();
}
