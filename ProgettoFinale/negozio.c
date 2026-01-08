/**
 * @file negozio.c
 * @brief Implementazione del negozio ambulante.
 */
#include <stdio.h>
#include <stdlib.h>
#include "negozio.h"
#include "systemclear.h"

void negozio(Giocatore* giocatore_ptr) {
    puliscischermo();
    printf("===== NEGOZIO AMBULANTE =====\n");
    printf("Mercante: 'Benvenuto straniero! Cosa vuoi comprare?'\n\n");
    printf("Monete disponibili: %d\n", giocatore_ptr->monete);
    printf("1. Pozione Curativa (4 monete)  - Ripristina 1d6 vita\n");
    printf("2. Spada di Ferro   (5 monete)  - +1 Attacco (Una volta)\n");
    printf("3. Armatura Leggera (10 monete) - -1 Danno subito (Una volta)\n");
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
            printf("Bevi la pozione... Ti senti meglio! (+%d HP)\n", cura);
        } else printf("Mercante: 'Non hai abbastanza oro per la pozione!'\n");
    } 
    else if (scelta == 2) {
        if (giocatore_ptr->ha_spada || giocatore_ptr->ha_spada_eroe) 
            printf("Mercante: 'Hai gia' un'arma valida, non te ne serve un'altra.'\n");
        else if (giocatore_ptr->monete >= 5) {
            giocatore_ptr->monete -= 5;
            giocatore_ptr->attacco += 1;
            giocatore_ptr->ha_spada = true;
            printf("Mercante: 'Maneggiala con cura!' (Spada acquistata)\n");
        } else printf("Mercante: 'Torna quando sarai piu' ricco!'\n");
    }
    else if (scelta == 3) {
        if (giocatore_ptr->ha_armatura) 
            printf("Mercante: 'Indossi gia' la mia armatura migliore!'\n");
        else if (giocatore_ptr->monete >= 10) {
            giocatore_ptr->monete -= 10;
            giocatore_ptr->ha_armatura = true;
            printf("Mercante: 'Questa ti salvera' la pelle.' (Armatura acquistata)\n");
        } else printf("Mercante: 'Costa troppo per te.'\n");
    }
    
    printf("Premi INVIO per tornare all'avventura...");
    getchar();
}