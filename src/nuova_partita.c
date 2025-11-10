#include <stdio.h>
#include <stdlib.h>



/*
+ - - - - - - - - - - - - - - - - - - - - - - - - - +
|                  [nome gioco]                     |
| nuova partita                                     |
| carica salvataggio                                |
+ - - - - - - - - - - - - - - - - - - - - - - - - - +
scegli un'opzione:

*/


void clear_screen(){
    #ifdef _WIN32
        system("cls");          // pulisce temrinale windows
    #elif __APPLE__
        system("clear");        // pulisce terminale macOS
    #else
        system("clear");        // pulisce terminale linux
    #endif
    
    return;
}

void arrow_navigation(){
    // TODO
    return;
}
void new_game(){
    int action;

    clear_screen();

    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    printf("|               La Fuga dal while(1)                |\n");
    printf("| 1) nuova partita                                  |\n");
    printf("| 2) carica salvataggio                             |\n");  
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    
    printf("scegli un'opzione: ");    
    scanf("%d", &action);       // la scelta deve essere 1/2 (int)

    if (action != 1 && action != 2) {
        printf("Scelta non valida, inserisci 1 o 2! \n");
        new_game();  // richiamo la funzione per far scegliere di nuovo
    }

    return;
}

int main(void) {
    system("clear");
    new_game();
    return 0;
}