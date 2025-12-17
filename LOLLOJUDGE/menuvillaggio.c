#include <stdio.h>
#include <stdlib.h>
#include "menuvillaggio.h"
#include "menuMissioni.h"
#include "inventario.h"
#include "systemclear.h"

void menuVillaggio(Giocatore* giocatore_ptr) {
    while (1) {
        puliscischermo();
        printf("===== VILLAGGIO =====\n");
        printf("1. Intraprendi missione\n");
        printf("2. Riposati (Ripristina vita)\n");
        printf("3. Inventario\n");
        printf("4. Salva (Non implementato)\n");
        printf("5. Esci dal gioco\n");
        printf("Scelta: ");
        
        int scelta;
        scanf("%d", &scelta);
        while(getchar() != '\n');

        if (scelta == 1) {
            Menu(giocatore_ptr); 
            
            // --- MODIFICA QUI: GESTIONE GAME OVER ---
            if (giocatore_ptr->vita <= 0) {
                puliscischermo();
                printf("\n=======================================\n");
                printf("             GAME OVER                 \n");
                printf("=======================================\n");
                printf("Il tuo eroe e' caduto in battaglia.\n");
                printf("L'avventura termina qui.\n\n");
                printf("Premi INVIO per chiudere il gioco...");
                getchar(); // Questa è la pausa che ti mancava!
                return;    // Esce e chiude il programma
            }
            // ----------------------------------------
        }
        else if (scelta == 2) {
            // Riposo: puoi farlo solo se hai monete? O gratis?
            // Il PDF dice: "riporta a 20 PUNTI VITA il personaggio"
            giocatore_ptr->vita = 20;
            printf("Ti sei riposato alla locanda. Vita ripristinata al massimo (20).\n");
            printf("Premi INVIO per continuare..."); // Aggiunta pausa per leggibilità
            getchar();
        }
        else if (scelta == 3) {
            puliscischermo();
            Inventario(giocatore_ptr);
            printf("\nPremi INVIO per tornare al villaggio...");
            getchar();
        }
        else if (scelta == 5) {
            return;
        }
    }
}