#include <stdio.h>
#include <stdlib.h>
#include "negozio.h"
#include "systemclear.h"

void negozio(Giocatore* giocatore_ptr) {
    puliscischermo();
    printf("===== NEGOZIO =====\n");
    printf("Monete attuali: %d\n\n", giocatore_ptr->monete);
    printf("1. Pozione Curativa (4 monete) - Ripristina 1d6 vita\n");
    printf("2. Spada (5 monete) - +1 Attacco\n");
    printf("3. Armatura (10 monete) - -1 Danno subito\n");
    printf("4. Esci\n");
    printf("Scelta: ");
    
    int scelta;
    scanf("%d", &scelta);
    while(getchar() != '\n');

    if (scelta == 1) {
        if (giocatore_ptr->monete >= 4) {
            giocatore_ptr->monete -= 4;
            int cura = (rand() % 6) + 1;
            giocatore_ptr->vita += cura;
            if (giocatore_ptr->vita > 20) giocatore_ptr->vita = 20;
            printf("Ti sei curato di %d punti vita!\n", cura);
        } else printf("Monete insufficienti!\n");
    } 
    else if (scelta == 2) {
        if (giocatore_ptr->ha_spada) printf("Hai gia' una spada!\n");
        else if (giocatore_ptr->monete >= 5) {
            giocatore_ptr->monete -= 5;
            giocatore_ptr->attacco += 1;
            giocatore_ptr->ha_spada = true;
            printf("Spada acquistata!\n");
        } else printf("Monete insufficienti!\n");
    }
    else if (scelta == 3) {
        if (giocatore_ptr->ha_armatura) printf("Hai gia' un'armatura!\n");
        else if (giocatore_ptr->monete >= 10) {
            giocatore_ptr->monete -= 10;
            giocatore_ptr->ha_armatura = true;
            printf("Armatura acquistata!\n");
        } else printf("Monete insufficienti!\n");
    }
    
    printf("Premi INVIO...");
    getchar();
}