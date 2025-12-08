#include <stdio.h>
#include "negozio.h"

void negozio(Giocatore* giocatore_ptr) {
    printf("Benvenuto nel negozio della Palude Putrescente!\n");
    printf("1. Pozione Curativa (+6 Vita) - 4 Monete\n");
    printf("2. Spada (+1 Attacco) - 5 Monete\n");
    printf("3. Armatura (+1 Difesa/Vita) - 10 Monete\n");
    printf("Scegli un'opzione (1-3) o 0 per uscire:\n");

    int scelta_negozio;
    scanf("%d", &scelta_negozio);

    switch(scelta_negozio) {
        case 1:
            if(giocatore_ptr->monete >= 4) {
                giocatore_ptr->vita += 6;
                giocatore_ptr->monete -= 4;
                printf("Hai acquistato una Pozione Curativa. Vita: %d.\n", giocatore_ptr->vita);
            } else {
                printf("Non hai abbastanza monete!\n");
            }
            break;
        case 2:
            if(giocatore_ptr->monete >= 5) {
                giocatore_ptr->attacco += 1;
                giocatore_ptr->monete -= 5;
                printf("Hai acquistato una Spada. Attacco: %d.\n", giocatore_ptr->attacco);
            } else {
                printf("Non hai abbastanza monete!\n");
            }
            break;
        case 3:
            if(giocatore_ptr->monete >= 10) {
                giocatore_ptr->vita += 1; 
                giocatore_ptr->monete -= 10;
                printf("Hai acquistato un'Armatura!\n");
            } else {
                printf("Non hai abbastanza monete!\n");
            }
            break;
        case 0:
            printf("Uscita dal negozio.\n");
            break;
        default:
            printf("Opzione non valida.\n");
    }
}