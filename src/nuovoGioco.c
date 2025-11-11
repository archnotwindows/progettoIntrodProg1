#include <stdio.h>
#include <stdlib.h>
#include "pulisciSchermo.h"
#include "nuovoGioco.h"

void nuovoGioco(){
    int action;

    pulisciSchermo();

    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    printf("|               La Fuga dal while(1)                |\n");
    printf("| 1) nuova partita                                  |\n");
    printf("| 2) carica salvataggio                             |\n");  
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    
    printf("scegli un'opzione: ");    
    scanf("%d", &action);       // la scelta deve essere 1/2 (int)

    if (action != 1 && action != 2) {
        printf("Scelta non valida, inserisci 1 o 2! \n");
        nuovoGioco();  // richiamo la funzione per far scegliere di nuovo
    }

    return;
}