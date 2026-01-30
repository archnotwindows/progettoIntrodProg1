/**
 * @file negozio.c
 * @brief Implementazione del sistema del Negozio.
 * * Questo file gestisce l'interazione con il mercante
 */

#include <stdio.h>
#include <stdlib.h>
#include "negozio.h"
#include "systemclear.h"

/**
 * @brief Visualizza il menu del negozio e gestisce gli acquisti.
 * * La funzione verifica che il giocatore abbia abbastanza monete e che
 * non possieda già l'oggetto che vuole acquistare 
 * * @param giocatore_ptr Puntatore alla struttura dati del giocatore
 */
void negozio(Giocatore* giocatore_ptr) {
    puliscischermo();
    printf("===== NEGOZIO =====\n");
    printf("Mercante: 'Benvenuto straniero! Cosa vuoi comprare?'\n\n");
    
    /* Mostra il saldo attuale del giocatore */
    printf("Monete disponibili: %d\n", giocatore_ptr->monete);
    
    printf("1. Pozione Curativa (4 monete)  - Ripristina 1d6 vita\n");
    printf("2. Spada di Ferro   (5 monete)  - +1 Attacco (Una volta)\n");
    printf("3. Armatura Leggera (10 monete) - -1 Danno subito (Una volta)\n");
    printf("4. Esci\n");
    printf("Scelta: ");
    
    /* Gestione input */
    int scelta;
    scanf("%d", &scelta);
    while(getchar() != '\n'); // Pulizia buffer input 

    /* --- Opzione 1: Cura --- */
    if (scelta == 1) {
        /* Controllo saldo */
        if (giocatore_ptr->monete >= 4) {
            giocatore_ptr->monete -= 4;
            
            /* Calcolo cura: dado a 6 facce (1-6 HP) */
            int cura = (rand() % 6) + 1;
            giocatore_ptr->vita += cura;
            
            /** * @brief Cap della Vita.
             * La vita non può superare il valore massimo di 20.
             */
            if (giocatore_ptr->vita > 20) giocatore_ptr->vita = 20;
            
            printf("Bevi la pozione... Ora ti senti meglio! (+%d HP)\n", cura);
        } else {
            printf("Mercante: 'Non hai abbastanza oro per la pozione!'\n");
        }
    } 
    /* --- Opzione 2: Spada (Oggetto Unico) --- */
    else if (scelta == 2) {
        /**
         * @brief Controllo ridondanza.
         * Impedisce l'acquisto se il giocatore ha già la spada di ferro OPPURE
         * se possiede già la Spada dell'Eroe.
         */
        if (giocatore_ptr->ha_spada || giocatore_ptr->ha_spada_eroe) {
            printf("Mercante: 'Hai gia' un'arma valida, non te ne serve un'altra.'\n");
        }
        /* Controllo saldo */
        else if (giocatore_ptr->monete >= 5) {
            giocatore_ptr->monete -= 5;
            giocatore_ptr->attacco += 1;    // Incremento permanente attacco 
            giocatore_ptr->ha_spada = true; // Flag inventario 
            printf("Mercante: 'Fanne buon uso!' (Spada acquistata)\n");
        } else {
            printf("Mercante: 'Torna quando sarai piu' ricco!'\n");
        }
    }
    /* --- Opzione 3: Armatura --- */
    else if (scelta == 3) {
        /**
         * @brief Controllo ridondanza armatura.
         * Verifica se l'armatura è già posseduta.
         */
        if (giocatore_ptr->ha_armatura) {
            printf("Mercante: 'Indossi gia' la mia armatura migliore!'\n");
        }
        /* Controllo saldo */
        else if (giocatore_ptr->monete >= 10) {
            giocatore_ptr->monete -= 10;
            giocatore_ptr->ha_armatura = true; // Flag per riduzione danni 
            printf("Mercante: 'Questa ti salvera' la pelle.' (Armatura acquistata)\n");
        } else {
            printf("Mercante: 'Costa troppo per te.'\n");
        }
    }
    /* Se scelta == 4 o altro, esce semplicemente dalla funzione  */
    
    printf("Premi INVIO per tornare all'avventura...");
    getchar();
}