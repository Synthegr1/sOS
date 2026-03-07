//Fonction pour intteroger un port processeur (port)
static inline unsigned char inb(unsigned short port) {
    unsigned char val; //On définit val comme ce qui sera la réponse du port
    asm volatile ("inb %1, %0" : "=a"(val) : "Nd"(port)); //On demande au processeur avec 'asm'
    return val; //On retourne 'asm'
}

//'asm' ajit comme si on disait au C : "Tu sais pas faire ça, on s'en fiche, demande le au processeur tkt !"

//Mémoire Vidéo VGA : Il y a des positions où on peut écrire sur l'écran, chaque psoition fait
//2 octets, 1 pour le caractère à afficher et 1 pour la couleur et le fond (ex : vert sur fond noir (sur dcp le 2e octet) = 0x02)

//Fonction équivalent printf, à executer avec comme argument l'élément a afficher, la postion x,
//la position y et la couleur (ex : vert = 0x01)
void print_at(const char* input, int x, int y, int color){
    volatile char* video_memory = (volatile char*)0xb8000; //On définit l'emplacement de la mémoire vidéo VGA

    int pos = (y * 80 + x) * 2; //Position du curseur x y ou on va écrire le texte
    for(int i = 0; input[i] != '\0'; i++){ //For pour l'écriture des différents caractères du char input un par un
        video_memory[pos] = input[i]; //on écrit le caractère sur le premier octet de l'emplacement vidéo
        video_memory[pos + 1] = color; //on écrit le couleur et le fond sur le deuxième octet de l'emplacement vidéo
        pos += 2; //On rajoute 2 au curseur pour le caractère suivant (caractère + mise en forme)
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

/*Fonction du logo*/
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

/*Fonction de clear de l'écran*/
void clear(){
    volatile char* video_memory = (volatile char*)0xb8000; //On prend l'emplacement de la mémoire Vidéo VGA
    for (int i = 0; i < 80 * 25 * 2; i += 2) { //For pour passer par tous les emplacements VGA de l'écran
        video_memory[i] = ' '; //On remplace par du vide
        video_memory[i+1] = 0x07;//Blanc sur fond noir
    }
}

/*Bureau*/
void bureau(){
    clear(); //On appelle la fonction 'clear' pour vider l'écran
    print_at("sOS -- Main :", 0, 0, 0x03); //Texte affiché en bleu cyan sur fond noir
    print_at("Vous tapez : ", 0, 1, 0x02); //Texte affiché en vert sur fond noir
    
    int cursor_x = 14; //On définit un curseur x
    while (1) /*__asm__ volatile ("hlt")*/{
        char c = input();
        if(c > 0){
            char str[2] = {c, "\0" && c != '?'}; //on met l input dans un char si c différent de '?'
            print_at(str, cursor_x++, 1, 0x02); //On affiche en vert (0x02)
        }
    }
}

//Fonction delay
void delay(int count){ //Prend count en entrée pour indiqué a peu près le temps d'attente voulu (70 = (2-3 sec))
    for(int x = 0; x < count * 10000000; x++){ //For avec le count multiplié par un million pour occuper le processeurs ce qui créé l'attente
        asm volatile("nop"); //On ne fait rien
    }
}

/*Fonction principale appelé par le linker.ld*/
void main() {
    clear(); //
    afficher_logo();
    delay(70);
    bureau();
}