#include "shell.h"
#include "util.h"
#include "kernel.h"

void help(int posdeb) {
    posdeb += 1;
    print_at("help", 0, posdeb, 0x0C);
    print_at(" -> List of all commands", 9, posdeb, 0x0F);

    posdeb += 1;
    print_at("shutdown", 0, posdeb, 0x0C);
    print_at(" -> Turn off the computer", 9, posdeb, 0x0F);

    posdeb += 1;
    print_at("color", 0, posdeb, 0x0C);
    print_at(" -> Color settings for echo", 9, posdeb, 0x0F);

        posdeb += 1;
        print_at("* all", 13, posdeb, 0x0B);
        print_at(" -> List all colors IDs", 18, posdeb, 0x0F);

        posdeb += 1;
        print_at("* color_id", 13, posdeb, 0x0B);
        print_at("-> Setup a color", 24, posdeb, 0x0F);

    posdeb += 1;
    print_at("echo", 0, posdeb, 0x0C);
    print_at(" -> Print text on the terminal", 9, posdeb, 0x0F);

    posdeb += 1;
    print_at("clear", 0, posdeb, 0x0C);
    print_at(" -> Clear the console", 9, posdeb, 0x0F);

    posdeb += 1;
    print_at("maths", 0, posdeb, 0x0C);
    print_at(" -> Perform arithmetic operations", 9, posdeb, 0x0F);

        posdeb += 1;
        print_at("* add", 13, posdeb, 0x0B);
        print_at("X",19, posdeb, 0x0E);
        print_at("u",21, posdeb, 0x01);
        print_at("Y",23, posdeb, 0x0E);
        print_at("-> Add X and Y",25, posdeb, 0x0F);

        posdeb += 1;
        print_at("* mul", 13, posdeb, 0x0B);
        print_at("X",19, posdeb, 0x0E);
        print_at("u",21, posdeb, 0x01);
        print_at("Y",23, posdeb, 0x0E);
        print_at("-> Multiply X and Y",25, posdeb, 0x0F);

        posdeb += 1;
        print_at("* div", 13, posdeb, 0x0B);
        print_at("X",19, posdeb, 0x0E);
        print_at("u",21, posdeb, 0x01);
        print_at("Y",23, posdeb, 0x0E);
        print_at("-> Divide X and Y",25, posdeb, 0x0F);

        posdeb += 1;
        print_at("* dec", 13, posdeb, 0x0B);

            posdeb += 1;
            print_at("* log",19, posdeb, 0x0D);
            print_at("X",25, posdeb, 0x0E);
            print_at("u",27, posdeb, 0x01);
            print_at("Y",29, posdeb, 0x0E);

            posdeb += 1;
            print_at("* ln",19, posdeb, 0x0D);
            print_at("X",25, posdeb, 0x0E);
            print_at("u",27, posdeb, 0x01);
            print_at("Y",29, posdeb, 0x0E);

            posdeb += 1;
            print_at("* div",19, posdeb, 0x0D);
            print_at("X",25, posdeb, 0x0E);
            print_at("u",27, posdeb, 0x01);
            print_at("Y",29, posdeb, 0x0E);

            posdeb += 1;
            print_at("* add",19, posdeb, 0x0D);
            print_at("X",25, posdeb, 0x0E);
            print_at("u",27, posdeb, 0x01);
            print_at("Y",29, posdeb, 0x0E);

            posdeb += 1;
            print_at("* mul",19, posdeb, 0x0D);
            print_at("X",25, posdeb, 0x0E);
            print_at("u",27, posdeb, 0x01);
            print_at("Y",29, posdeb, 0x0E);

        posdeb += 1;
        print_at("* neg", 13, posdeb, 0x0B);

}

int colorselect(char *thinks){
    int echocolor;
    int taillechar = sizeOf(thinks);
        int y = 6;
        int j = 0;
        if(taillechar > y){
            char buffer[100];
            for(int i = y; i < taillechar; i++){
                buffer[j++] = thinks[i];
            }
            buffer[j] = '\0';

            if (compchar(buffer, "black")){
                echocolor = 0x00;
                return echocolor;
            }
            else if(compchar(buffer, "white")){
                echocolor = 0xF;
                return echocolor;
            }
            else if(compchar(buffer, "blue1")){
                echocolor = 0x01;
                return echocolor;
            }
            else if(compchar(buffer, "green1")){
                echocolor = 0x02;
                return echocolor;
            }
            else if(compchar(buffer, "cyan1")){
                echocolor = 0x03;
                return echocolor;
            }
            else if(compchar(buffer, "red1")){
                echocolor = 0x04;
                return echocolor;
            }
            else if(compchar(buffer, "magenta1")){
                echocolor = 0x05;
                return echocolor;
            }
            else if(compchar(buffer, "marron")){
                echocolor = 0x06;
                return echocolor;
            }
            else if(compchar(buffer, "grey1")){
                echocolor = 0x07;
                return echocolor;
            }
            else if(compchar(buffer, "grey2")){
                echocolor = 0x08;
                return echocolor;
            }
            else if(compchar(buffer, "blue2")){
                echocolor = 0x09;
                return echocolor;
            }
            else if(compchar(buffer, "green2")){
                echocolor = 0x0A;
                return echocolor;
            }
            else if(compchar(buffer, "cyan2")){
                echocolor = 0x0B;
                return echocolor;
            }
            else if(compchar(buffer, "red2")){
                echocolor = 0x0C;
                return echocolor;
            }
            else if(compchar(buffer, "magenta2")){
                echocolor = 0x0D;
                return echocolor;
            }
            else if(compchar(buffer, "yellow")){
                echocolor = 0x0E;
                return echocolor;
            } else if(compchar(buffer, "all")){
                return 2;
            } else if(compchar(buffer, "help")){
                return 3;
            } else {
                return 404;
            }
        }
}

int is_an_int(char input){
    switch(input){
        case '0':
            return 1;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 1;
            break;
        case '3':
            return 1;
            break;
        case '4':
            return 1;
            break;
        case '5':
            return 1;
            break;
        case '6':
            return 1;
            break;
        case '7':
            return 1;
            break;
        case '8':
            return 1;
            break;
        case '9':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

char buffer1[100];
char buffer2[100];
char buffer3[100];

char proprechar1[10];
char proprechar2[10];

void extract_2_values(char *input){
    clearBuffer(proprechar1);
    clearBuffer(proprechar2);

    int g = 0;
    int who = 1;
    int o = 0;
    int m = 0;

    while(input[g] != '\0'){
        if(is_an_int(input[g]) == 1 || input[g] == ','){
            if(who == 1){
                proprechar1[o] = input[g];
                o += 1;
            } else if(who == 2){
                proprechar2[m] = input[g];
                m += 1;
            }
        } else if(input[g] == 'u'){
            proprechar1[o] = '\0';
            who = 2;
        }
        g += 1;
    }
    proprechar2[m] = '\0';
}

// --- Opérations d'entiers --- //
int operate(char *input){
    clearBuffer(buffer1);
    clearBuffer(buffer2);

    int charsize = sizeOf(input);
    int y = sizeOf("maths") + 1;
    int cursor = 0;
    if(charsize > y){
        for(int i = y; i < charsize; i++){
            buffer1[cursor] = input[i];
            cursor += 1;
        }
        buffer1[cursor] = '\0';

    cursor = 0;
    int charsize2 = sizeOf(buffer1);
    int j = 4;
    if(charsize2 > j){
        for(int i = j; i < charsize2; i++){
            buffer2[cursor] = buffer1[i];
            cursor += 1;
        }

        extract_2_values(buffer2);

        int k = convertCharToInt(proprechar1);
        int l = convertCharToInt(proprechar2);

        if(compchar(buffer1, "add")){
            return k + l;
        } else if(startsWith(buffer1, "div")){
            if(k != 0 && l != 0){
                return (k / l);
            } else {
                return 404;
            }
        } else if(compchar(buffer1, "mul")){
            return k * l;
        }
        //DECIMAUX
        else if (startsWith(buffer1, "dec")) {
            dec_operate(buffer1);
        }
    }
}

    clearBuffer(buffer1);
    clearBuffer(buffer2);
    clearBuffer(buffer3);

}

// --- Opérations avec des décimaux --- //
double dec_operate(char *input) {
    int charsize = sizeOf(input);
    int y = 5;
    int cursor = 0;
    if(charsize > y){
        for(int i = y; i < charsize; i++){
            buffer1[cursor] = input[i];
            cursor += 1;
        }
        buffer1[cursor] = '\0';

        cursor = 0;
        int charsize2 = sizeOf(buffer1);
        int j = 4;
        if(charsize2 > j){
            for(int i = j; i < charsize2; i++){
                buffer2[cursor] = buffer1[i];
                cursor += 1;
            }

            cursor = 0;
            int charsize3 = sizeOf(buffer2);
            int p = 4;
            if(charsize3 > p){
                for(int i = p; i < charsize3; i++){
                    buffer3[cursor] = buffer2[i];
                    cursor += 1;
                }

                extract_2_values(buffer3);

                int k = convertCharToInt(proprechar1);
                int l = convertCharToInt(proprechar2);

                if (startsWith(buffer2, "div")) {
                    double result = (double)k / (double)l;
                    return result;
                }
                else if( startsWith(buffer2, "mul")) {

                }
                else if (startsWith(buffer2, "add")) {

                }
                else if( startsWith(buffer2, "log")) {

                }
                else if( startsWith(buffer2, "ln")) {

                }
            }

            clearBuffer(buffer1);
            clearBuffer(buffer2);
            clearBuffer(buffer3);
        }
    }
}

    //Fonction shell
    void run(char thinks[100]) {
        //print_at(thinks, 0, posdeb + 1, 0x04);
        if(compchar(thinks, "hello") == 1){
            print_at("world", 0, posdeb + 1, 0x01);

        } else if (compchar(thinks, "shutdown") == 1){
            outw(0x604, 0x2000);

        } else if ( compchar(thinks, "clear") == 1){
            clear();
            bureau();

        } else if(startsWith(thinks, "noemie") == 1){
            print_at("Noemie est la plus belle fille que j'ai rencontre sur terre,", 0, posdeb + 1, 0x05);
            posdeb += 1;
            print_at("elle est le soleil de ma vie ! <3", 0, posdeb + 1, 0x05);

        } else if(startsWith(thinks, "echo")){
            int taillechar = sizeOf(thinks);
            int y = 5;
            int j = 0;
            if(taillechar > y){
                char buffer[100];
                for(int i = y; i < taillechar; i++){
                    buffer[j++] = thinks[i];
                }
                buffer[j] = '\0';
                print_at(buffer, 0, posdeb + 1, echocolor);
            }
        } else if(startsWith(thinks, "color")){
            if(colorselect(thinks) == 2){
                posdeb += 1;
                print_at("blue1", 0, posdeb, 0x01);
                print_at("green1", 7, posdeb, 0x02);
                print_at("cyan1", 14, posdeb, 0x03);
                print_at("red1", 20, posdeb, 0x04);
                posdeb += 1;
                print_at("magenta1", 0, posdeb, 0x05);
                print_at("marron", 9, posdeb, 0x06);
                print_at("grey1", 16, posdeb, 0x07);
                print_at("grey2", 22, posdeb, 0x08);
                posdeb += 1;
                print_at("bleu2", 0, posdeb, 0x09);
                print_at("green2", 6, posdeb, 0x0A);
                print_at("cyan2", 13, posdeb, 0x0B);
                print_at("red2", 19, posdeb, 0x0C);
                posdeb += 1;
                print_at("magenta2", 0, posdeb, 0x0D);
                print_at("yellow", 9, posdeb, 0x0E);
                print_at("white", 16, posdeb, 0x0F);
                posdeb -= 1;
            }else if(colorselect(thinks) == 3){
                posdeb += 1;
                print_at("For use the command \'color\' you need to put the \'color\' keyword and", 0, posdeb, 0x0A);
                print_at("after the name of the color. For see all colors, press the arguments", 0, posdeb + 1, 0x0A);
                print_at("\'all\'. Exemple : -color all- (see alls colors) or -color white-", 0, posdeb + 2, 0x0A);
                print_at("(color set in white)", 0, posdeb + 3, 0x0A);
                posdeb += 2;
            } else if(colorselect(thinks) == 404) {
                print_at("Error : invalid color !", 0, posdeb + 1, 0x04);
            } else {
                echocolor = colorselect(thinks);
            }


        } else if(compchar(thinks, "help")){
            help(posdeb);
            posdeb += 17;
        }
        else if(startsWith(thinks, "maths ")) {
            char s[10];
            /*if (startsWith(thinks, "maths dec")) {
                double r = dec_operate(thinks);
                convertDecimalToChar(r, s);
                print_at(s, posdeb + 1, posdeb + 5, posdeb + 6);
            }else {*/
                int y = operate(thinks);
                convertIntTOChar(y, s);
                print_at(s, 0, posdeb + 1, 0x04);
        //}
        }
        else if (compchar(thinks, "test")) {
            char v[10];
            convertDecimalToChar(78.65, v);
            print_at(v, 0, posdeb + 1, 0x09);
        }
        else {
            print_at("Invalid command", 0, posdeb + 1, 0x04);
        }
    }

