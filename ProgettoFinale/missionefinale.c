/**
 * @file missionefinale.c
 * @brief Implementazione del combattimento finale contro il Signore Oscuro.
 * * Questo file gestisce l'ultimo ostacolo del gioco. Il sistema di combattimento utilizzato é un minigioco strategico "Sasso-Carta-Forbice"
 * in cui il giocatore deve vincere 3 round su 5 contro l'avversario controllato dalla CPU.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "missionefinale.h"
#include "systemclear.h"

/**
 * @brief Genera la mossa dell'avversario.
 * @return Un intero rappresentante la mossa:
 * - 1: Scudo
 * - 2: Magia
 * - 3: Spada
 */
int mossarandom() {
    return (rand() % 3) + 1;
}

/**
 * @brief Gestisce il loop del combattimento finale.
 * * Le regole sono:
 * - Scudo (1) batte Spada (3)
 * - Magia (2) batte Scudo (1)
 * - Spada (3) batte Magia (2)
 * * Vince il primo che arriva a 3 vittorie.
 * * @param g Puntatore al giocatore (usato per azzerare la vita in caso di sconfitta).
 */
void CombattimentoFinale(Giocatore* g) {
    // Array di stringhe per decodificare gli indici delle mosse in testo
    char* nomi_mosse[3] = {"Scudo", "Magia", "Spada"};
    
    int vittorie_g = 0; // Contatore vittorie Giocatore 
    int vittorie_s = 0; // Contatore vittorie Signore Oscuro 
    int round = 1;      // Contatore Round corrente 

    puliscischermo();
    printf("=== SCONTRO FINALE CON IL SIGNORE OSCURO ===\n");
    printf("Regole: Scudo batte Spada, Magia batte Scudo, Spada batte Magia.\n");
    printf("Devi vincere 3 round su 5!\n\n");

    /**
     * @brief Loop principale dello scontro.
     * Continua finché non si raggiungono 5 round validi O finché uno dei due
     * contendenti non ottiene 3 vittorie (con maggioranza assoluta).
     */
    while (round <= 5 && vittorie_g < 3 && vittorie_s < 3) {
        int scelta_g;
        printf("\n--- Round %d ---\n", round);
        printf("1. Scudo\n2. Magia\n3. Spada\nScegli: ");
        
        scanf("%d", &scelta_g);
        while(getchar()!='\n'); /* Pulisce il buffer */

        /* Validazione input */
        if (scelta_g < 1 || scelta_g > 3) {
            printf("Mossa non valida!\n");
            continue;
        }

        /* Generazione mossa avversario */
        int scelta_s = mossarandom();
        
        /* Stampa resoconto turno */
        printf("Tu: %s vs Signore Oscuro: %s\n", nomi_mosse[scelta_g - 1], nomi_mosse[scelta_s - 1]);

        /* --- GESTIONE PAREGGIO --- */
        if (scelta_g == scelta_s) {
            printf("Pareggio! Il round si ripete.\n");
            /* "continue" salta l'incremento del round e ripete lo stesso turno */
            continue; 
        }

        /* --- GESTIONE VITTORIA --- */
        /**
         * @brief Verifica condizioni di vittoria.
         * vince_g è true se si verifica una delle tre condizioni di vantaggio.
         */
        bool vince_g = (scelta_g == 1 && scelta_s == 3) || /* Scudo > Spada */
                       (scelta_g == 2 && scelta_s == 1) || /* Magia > Scudo */
                       (scelta_g == 3 && scelta_s == 2);   /* Spada > Magia */

        if (vince_g) {
            printf(">> Hai vinto il round!\n");
            vittorie_g++;
        } else {
            printf(">> Il Signore Oscuro vince il round!\n");
            vittorie_s++;
        }
        
        round++; /* Avanza al prossimo round solo se non c'è stato pareggio */
    }

    /* --- RISOLUZIONE FINALE --- */
    if (vittorie_g >= 3) {
        printf("\n\n============================================\n");
        printf("   VITTORIA! IL SIGNORE OSCURO E' SCONFITTO!   \n");
        printf("============================================\n");
        printf("Hai salvato il villaggio e completato il gioco!\n");
        /* Il gioco termina positivamente qui */
    } else {
        printf("\n\n============================================\n");
        printf("   SCONFITTA... IL MONDO CADE NELLE TENEBRE   \n");
        printf("============================================\n");
        
        /**
         * @brief Imposta HP a 0 per Game Over.
         * Impostando la vita a 0, al ritorno nel menuVillaggio verrà
         * rilevata la morte del giocatore, attivando la schermata di Game Over.
         */
        g->vita = 0; 
    }
    
    printf("Premi INVIO...");
    getchar();
}