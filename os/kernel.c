int p = 0;
int posdeb = 1;

//Fonction pour intteroger un port processeur (port)

//unsigned char = 8 bits & unsigned short = 16 bits
static inline unsigned char inb(unsigned short port) {
    unsigned char val; //On définit val comme ce qui sera la réponse du port
    asm volatile ("inb %1, %0" : "=a"(val) : "Nd"(port)); //On demande au processeur avec 'asm'
    return val; //On retourne 'asm'
}

static inline void outw(unsigned short port, unsigned short val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
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
    while(!(inb(0x64) & 1)){ //On ATTEND que 0x064 soit égal à 1 (0 = pas pressé, 1 = pressé)
        asm volatile("pause"); //En attendant, on htl le proc pour qu il fasse rien et chauffe pas dans un while
    } 
    scancode = inb(0x60); //On récupère le scancode dans le port 0x60
    if (scancode & 0x80) return 0; //Sile scancode est > 128 c'est un relachement de touches
    if(scancode == 0x1C) return '\n';
    unsigned char map[] = "??1234567890??\b?azertyuiop??\n?qsdfghjklm????wxcvbn,?;? "; //Map des touches (à comparé avec le 0x60)
    if (scancode < sizeof(map)) { //Si le scancode fait partis de la map
        return map[scancode]; //On retourne la touche pressé
    }
    return 0; //Retour null si c pas bon
}

void afficher_logo(void){
    print_at("                               LL              .d88888b.    .d8888b.", 5, 8, 0x0E);
    print_at("                               LL             d888P" "Y888b  d88P  Y88b", 5, 9, 0x0E);
    print_at("         II                    LL            888     888  Y88b.", 5, 10, 0x0E);
    print_at(".dSSSSb                        LL            888     888   \"Y888b.", 5, 11, 0x0E);
    print_at("88K      II MMM.   .MMM PPPb.  LL   .dEEEb   888     888      \"Y88b.", 5, 12, 0x0E);
    print_at("\"YSSSSb. II MM \"M..M\"MM PP \"Yb LL .EE\"  \"EE. 888     888        \"888", 5, 13, 0x0E);
    print_at("     X88 II MM  \"MM\" MM PP .dP LL \"EE^^^^^^\" Y88b. .d88P  Y88b  d88P", 5, 14, 0x0E);
    print_at(" SSSSSP' II MM       MM PPPP   LL   \"YEEEP\"   \"YBBBBBP\"    \"Y8888P\"", 5, 15, 0x0E);
    print_at("                        PP", 5, 16, 0x0E);
    print_at("                        PP", 5, 17, 0x0E);
    print_at("                        PP", 5, 18, 0x0E);
    delay(30);
    clear();
    print_at("                               LL         .d88888b.    .d8888b.", 5, 8, 0x0E);
    print_at("                               LL        d888P" "Y888b  d88P  Y88b", 5, 9, 0x0E);
    print_at("         II                    LL       888     888  Y88b.", 5, 10, 0x0E);
    print_at(".dSSSSb                        LL       888     888   \"Y888b.", 5, 11, 0x0E);
    print_at("88K      II MMM.   .MMM PPPb.  LL   .dE 888     888      \"Y88b.", 5, 12, 0x0E);
    print_at("\"YSSSSb. II MM \"M..M\"MM PP \"Yb LL .EE\"  888     888        \"888", 5, 13, 0x0E);
    print_at("     X88 II MM  \"MM\" MM PP .dP LL \"EE^^ Y88b. .d88P  Y88b  d88P", 5, 14, 0x0E);
    print_at(" SSSSSP' II MM       MM PPPP   LL   \"YE  \"YBBBBBP\"    \"Y8888P\"", 5, 15, 0x0E); 
    print_at("                        PP", 5, 16, 0x0E);
    print_at("                        PP", 5, 17, 0x0E);
    print_at("                        PP", 5, 18, 0x0E);
    delay(5);
    clear();
    print_at("                               LL       .d88888b.    .d8888b.", 5, 8, 0x0E);
    print_at("                               LL      d888P" "Y888b  d88P  Y88b", 5, 9, 0x0E);
    print_at("         II                    LL     888     888  Y88b.", 5, 10, 0x0E);
    print_at(".dSSSSb                        LL     888     888   \"Y888b.", 5, 11, 0x0E);
    print_at("88K      II MMM.   .MMM PPPb.  LL   . 888     888      \"Y88b.", 5, 12, 0x0E);
    print_at("\"YSSSSb. II MM \"M..M\"MM PP \"Yb LL .EE 888     888        \"888", 5, 13, 0x0E);
    print_at("     X88 II MM  \"MM\" MM PP .dP LL \"EE Y88b. .d88P  Y88b  d88P", 5, 14, 0x0E);
    print_at(" SSSSSP' II MM       MM PPPP   LL   \"  \"YBBBBBP\"    \"Y8888P\"", 5, 15, 0x0E); 
    print_at("                        PP", 5, 16, 0x0E);
    print_at("                        PP", 5, 17, 0x0E);
    print_at("                        PP", 5, 18, 0x0E);
    delay(5);
    clear();
    print_at("                             LL    .d88888b.    .d8888b.", 7, 8, 0x0E);
    print_at("                             LL   d888P" "Y888b  d88P  Y88b", 7, 9, 0x0E);
    print_at("        I                    LL  888     888  Y88b.", 7, 10, 0x0E);
    print_at(".dSSSSb                      LL  888     888   \"Y888b.", 7, 11, 0x0E);
    print_at("88K     I MMM.   .MMM PPPb.  LL  888     888      \"Y88b.", 7, 12, 0x0E);
    print_at("\"YSSSSb.I MM \"M..M\"MM PP \"Yb LL .888     888        \"888", 7, 13, 0x0E);
    print_at("     X88I MM  \"MM\" MM PP .dP LL \"Y88b. .d88P  Y88b  d88P", 7, 14, 0x0E);
    print_at(" SSSSSP'I MM       MM PPPP   LL   \"YBBBBBP\"    \"Y8888P\"", 7, 15, 0x0E); 
    print_at("                        PP", 5, 16, 0x0E);
    print_at("                        PP", 5, 17, 0x0E);
    print_at("                        PP", 5, 18, 0x0E);
    delay(5);
    clear();
    print_at("                           LL .d88888b.    .d8888b.", 9, 8, 0x0E);
    print_at("                           LLd888P" "Y888b  d88P  Y88b", 9, 9, 0x0E);
    print_at("                           L888     888  Y88b.", 9, 10, 0x0E);
    print_at(".dSSSSb                    L888     888   \"Y888b.", 9, 11,      0x0E);
    print_at("88K     MMM.   .MMM PPPb.  L888     888      \"Y88b.", 9, 12, 0x0E);
    print_at("\"YSSSSb.MM \"M..M\"MM PP \"Yb L888     888        \"888", 9, 13, 0x0E);
    print_at("     X88MM  \"MM\" MM PP .dP LLY88b. .d88P  Y88b  d88P", 9, 14, 0x0E);
    print_at(" SSSSSP'MM       MM PPPP   LL\"YBBBBBP\"    \"Y8888P\"", 9, 15, 0x0E); 
    print_at("                        PP", 5, 16, 0x0E);
    print_at("                        PP", 5, 17, 0x0E);
    print_at("                        PP", 5, 18, 0x0E);
    delay(5);
    clear();    
    print_at("                         .d88888b.    .d8888b.", 11, 8, 0x0E);
    print_at("                        d888P" "Y888b  d88P  Y88b", 11, 9, 0x0E);
    print_at("                       888     888  Y88b.", 11, 10, 0x0E);
    print_at(".dSSSSb                888     888   \"Y888b.", 11, 11,      0x0E);
    print_at("88K     M.   .MMM PPPb.888     888      \"Y88b.", 11, 12, 0x0E);
    print_at("\"YSSSSb. \"M..M\"MM PP \"Y888     888        \"888", 11, 13, 0x0E);
    print_at("     X88  \"MM\" MM PP .dPY88b. .d88P  Y88b  d88P", 11, 14, 0x0E);
    print_at(" SSSSSP'       MM PPPP  \"YBBBBBP\"    \"Y8888P\"", 11, 15, 0x0E); 
    print_at("                  PP", 11, 16, 0x0E);
    print_at("                  PP", 11, 17, 0x0E);
    print_at("                  PP", 11, 18, 0x0E);
    delay(5);
    clear();
    print_at("                    .d88888b.    .d8888b.", 13, 8, 0x0E);
    print_at("                   d888P" "Y888b  d88P  Y88b", 13, 9, 0x0E);
    print_at("                  888     888  Y88b.", 13, 10, 0x0E);
    print_at(".dSSSSb           888     888   \"Y888b.", 13, 11,      0x0E);
    print_at("88K        .MMM PP888     888      \"Y88b.", 13, 12, 0x0E);
    print_at("\"YSSSSb.M..M\"MM PY888     888        \"888", 13, 13, 0x0E);
    print_at("     X88\"MM\" MM PPY88b. .d88P  Y88b  d88P", 13, 14, 0x0E);
    print_at(" SSSSSP'     MM PPP\"YBBBBBP\"    \"Y8888P\"", 13, 15, 0x0E);
    print_at("                PP", 13, 16, 0x0E);
    print_at("                PP", 13, 17, 0x0E);
    print_at("                PP", 13, 18, 0x0E);
    delay(5);
    clear();
    print_at("             .d88888b.    .d8888b.", 14, 8, 0x0E);
    print_at("            d888P" "Y888b  d88P  Y88b", 14, 9, 0x0E);
    print_at("           888     888  Y88b.", 14, 10, 0x0E);
    print_at(".dSSSSb    888     888   \"Y888b.", 14, 11,      0x0E);
    print_at("88K       .888     888      \"Y88b.", 14, 12, 0x0E);
    print_at("\"YSSSSb...M888     888        \"888", 14, 13, 0x0E);
    print_at("     X88MM\"Y88b. .d88P  Y88b  d88P", 14, 14, 0x0E);
    print_at(" SSSSSP'    \"YBBBBBP\"    \"Y8888P\"", 14, 15, 0x0E);
    delay(5);
    clear();
    print_at("          .d88888b.    .d8888b.", 15, 8, 0x0E);
    print_at("          d888P" "Y888b  d88P  Y88b", 14, 9, 0x0E);
    print_at("         888     888  Y88b.", 14, 10, 0x0E);
    print_at(".dSSSSb  888     888   \"Y888b.", 14, 11,      0x0E);
    print_at("88K      888     888      \"Y88b.", 14, 12, 0x0E);
    print_at("\"YSSSSb  888     888        \"888", 14, 13, 0x0E);
    print_at("     X88 Y88b. .d88P  Y88b  d88P", 14, 14, 0x0E);
    print_at(" SSSSSP'  \"YBBBBBP\"    \"Y8888P\"", 14, 15, 0x0E);
    delay(5);
    clear();
    print_at("          .d88888b.    .d8888b.", 20, 8, 0x0E);
    print_at("          d888P" "Y888b  d88P  Y88b", 20, 9, 0x0E);
    print_at("         888     888  Y88b.", 20, 10, 0x0E);
    print_at(".dSSSSb  888     888   \"Y888b.", 20, 11,      0x0E);
    print_at("88K      888     888      \"Y88b.", 20, 12, 0x0E);
    print_at("\"YSSSSb  888     888        \"888", 20, 13, 0x0E);
    print_at("     X88 Y88b. .d88P  Y88b  d88P", 20, 14, 0x0E);
    print_at(" SSSSSP'  \"YBBBBBP\"    \"Y8888P\"", 20, 15, 0x0E);
    delay(5);
    clear();
    print_at("          .d88888b.    .d8888b.", 24, 8, 0x0E);
    print_at("          d888P" "Y888b  d88P  Y88b", 24, 9, 0x0E);
    print_at("         888     888  Y88b.", 24, 10, 0x0E);
    print_at(".dSSSSb  888     888   \"Y888b.", 24, 11,      0x0E);
    print_at("88K      888     888      \"Y88b.", 24, 12, 0x0E);
    print_at("\"YSSSSb  888     888        \"888", 24, 13, 0x0E);
    print_at("     X88 Y88b. .d88P  Y88b  d88P", 24, 14, 0x0E);
    print_at(" SSSSSP'  \"YBBBBBP\"    \"Y8888P\"", 24, 15, 0x0E);
    delay(5);
}

/*Fonction de clear de l'écran*/
void clear(){
    volatile char* video_memory = (volatile char*)0xb8000; //On prend l'emplacement de la mémoire Vidéo VGA
    for (int i = 0; i < 80 * 25 * 2; i += 2) { //For pour passer par tous les emplacements VGA de l'écran
        video_memory[i] = ' '; //On remplace par du vide
        video_memory[i+1] = 0x0F;//Blanc sur fond noir
    }
}

typedef enum {
    false = 0,
    true = 1
} bool;

bool compchar(char a[100], char b[100]){
    int curs = 0;
    while(a[curs] != '\0' && b[curs] != '\0'){
        if(a[curs] != b[curs]){
            return false;
        }
        curs++;
    }
    return a[curs] == b[curs];
}

//Fonction delay
void delay(int count){ //Prend count en entrée pour indiqué a peu près le temps d'attente voulu (70 = (2-3 sec))
    for(int x = 0; x < count * 10000000; x++){ //For avec le count multiplié par un million pour occuper le processeurs ce qui créé l'attente
        asm volatile("nop"); //On ne fait rien
    }
}

void run(char thinks[100]) {
    //print_at(thinks, 0, posdeb + 1, 0x04);
    if(compchar(thinks, "hello")){
        print_at("world", 0, posdeb + 1, 0x01);
    } else if (compchar(thinks, "shutdown")){
        outw(0x604, 0x2000);
    } 
    else {
        print_at("Invalid command", 0, posdeb + 1, 0x04);
    }
}

/*Fonction principale appelé par le linker.ld*/
void main() {

    clear(); //
    afficher_logo();
    delay(70);/* code */
    clear();
    print_at("Main:", 0, 0, 0x03); //Texte affiché en bleu cyan sur fond noir
    print_at("sOS-bash$ ", 0, posdeb, 0x02); //Texte affiché en vert sur fond noir
    
    char text[100]; //On définit le char pour stocker TOUTE la commande
    int pos = 0; //Le curseur pour voyager dans text
    int cursor_x = 10; //On définit un curseur x
        while (1) {
            char c = input(); //On récupère la touche pressé dans c
            if (c == 0) { // Si c = 0 (un relachement de touche (voir ____input___))
                //On ne fait rien
            } else if (c == '\n'){ //Si c == a la touche entré (0xC1)
                run(text); //On run la commande (text[100])
                posdeb += 2;
                print_at("sOS-bash$ ", 0, posdeb, 0x02); //Texte affiché en vert sur fond noir
                cursor_x = 10;
                //char space[1] = "";
                for(int g = 0; g < 100; g++){
                    text[g] = '\0';
                    pos = 0;
                }
            } else if(c == '\b') { //Si c == \b (backspace)
                if(cursor_x > 9) {
                    cursor_x--;
                    print_at("  ", cursor_x, 1, 0x01);
                }
            } else if(c > 0) {             
                text[pos++] = c; //On écrit dans un char l'intégralité de la commande
                text[pos] = '\0'; //Rajouter \0 a tt les caractères
                char str[2] = {c, '\0'}; //On transforme le char en string pour pouvoir l'afficher
                print_at(str, cursor_x++, posdeb, 0x07); //Afficher le caractère
            }
            //asm volatile("pause");
        }
    
    
}
