//Fonction pour intteroger un port processeur (port)
static inline unsigned char inb(unsigned short port) {
    unsigned char val;
    asm volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

void print_at(const char* input, int x, int y, int color){
    volatile char* video_memory = (volatile char*)0xb8000;

    int pos = (y * 80 + x) * 2;
    for(int i = 0; input[i] != '\0'; i++){
        video_memory[pos] = input[i];
        video_memory[pos + 1] = color;
        pos += 2;
    }
}

//______INPUT_______
//Pour communiquer avec le clavier, il y a 2 ports : 0x64, qui permet de savoir si une touche 
//est pressé et 0x60 qui donne le code de la touche.
char input() {
    unsigned char scancode; //Définission de scancode qui est la valeur retourné par le clavier
    while(!(inb(0x64) & 1)); //On ATTEND que 0x064 soit égal à 1 (0 = pas pressé, 1 = pressé)
    scancode = inb(0x60); //On récupère le scancode dans le port 0x60
    if (scancode & 0x80) return 0; //Sile scancode est > 128 c'est un relachement de touches
    unsigned char map[] = "??1234567890??\b?azertyuiop???\n?qsdfghjkl???wxcvbn,?;? "; //Map des touches (à comparé avec le 0x60)
    if (scancode < sizeof(map)) { //Si le scancode fait partis de la map
        return map[scancode]; //On retourne la touche pressé
    }
    return 0; //Retour null si c pas bon
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
    print_at("sOS -- Main :", 0, 0, 0x03);
    print_at("Vous tapez : ", 0, 1, 0x02);
    
    int cursor_x = 14; //On définit un curseur x
    while (1) /*__asm__ volatile ("hlt")*/{
        char c = input();
        if(c > 0){
            char str[2] = {c, "\0" && c != '?'}; //on met l input dans un char si c différent de '?'
            print_at(str, cursor_x++, 1, 0x02); //On affiche en vert (0x02)
        }
    }
}

void delay(int count){
    for(int x = 0; x < count * 10000000; x++){
        asm volatile("nop");
    }
}

/*fonction principale*/
void main() {
    clear();
    afficher_logo();
    delay(70);
    bureau();
}